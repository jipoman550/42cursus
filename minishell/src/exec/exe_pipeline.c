/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 09:59:02 by hama              #+#    #+#             */
/*   Updated: 2026/07/07 12:25:53 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

static int	all_wait_pid(pid_t *pid, int cmd_cnt)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 1;
	while (i < cmd_cnt)
	{
		while (waitpid(pid[i], &status, 0) == -1)
		{
			if (errno == EINTR)
				continue ;
		}
		if (i == cmd_cnt - 1)
			last_status = decode_wait_status(status);
		i++;
	}
	free(pid);
	if (WIFSIGNALED(last_status) && WTERMSIG(last_status) == SIGINT)
		write(1, "\n", 1);
	if (WIFSIGNALED(last_status) && WTERMSIG(last_status) == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
	set_signal_interactive();
	return (last_status);
}

static void	pipe_child(t_cmd *cmd, t_pipeline *p, t_shell *sh, t_mix m)
{
	int	status;

	set_signal_dfl();
	if (set_std_inout(m.i, m.cmd_cnt, m, cmd) != 0)
		pipe_clean_up(p, sh, m.pid, 1);
	if (cmd->is_builtin || is_builtin(cmd->argv[0]))
	{
		status = exe_builtin(p, cmd, sh);
		pipe_clean_up(p, sh, m.pid, status);
	}
	status = exe_external(p, cmd, sh);
	pipe_clean_up(p, sh, m.pid, status);
}

static	int	pipe_excute(t_pipeline *p, t_shell *sh, t_mix m)
{
	while (m.i < m.cmd_cnt)
	{
		m.pipefd[0] = -1;
		m.pipefd[1] = -1;
		if (m.i != m.cmd_cnt - 1 && pipe(m.pipefd) < 0)
			return (perror("pipe"), err_p_f(m.pid, m.i, m.prev, m.pipefd));
		m.pid[m.i] = fork();
		if (m.pid[m.i] < 0)
			return (perror("fork"), err_p_f(m.pid, m.i, m.prev, m.pipefd));
		if (m.pid[m.i] == 0)
			pipe_child(m.cmd, p, sh, m);
		if (m.i != m.cmd_cnt - 1)
		{
			close(m.pipefd[1]);
			m.prev = m.pipefd[0];
		}
		else if (m.prev != -1)
			close(m.prev);
		m.cmd = m.cmd -> next;
		m.i++;
	}
	return (all_wait_pid(m.pid, m.cmd_cnt));
}

static	int	run_pipeline(t_pipeline *p, t_cmd *cmd, t_shell *sh, int cmd_cnt)
{
	t_mix	m;

	if (is_empty_cmd(cmd))
		return (0);
	m.pid = malloc(sizeof(pid_t) * cmd_cnt);
	if (!m.pid)
		return (perror("malloc"), 1);
	m.prev = -1;
	m.cmd_cnt = cmd_cnt;
	m.cmd = cmd;
	m.i = 0;
	set_signal_ign();
	return (pipe_excute(p, sh, m));
}

void	exe_pipeline(t_pipeline *p, t_shell *sh)
{
	int		n;
	int		status;

	if (!p || !p->cmds)
		return ;
	if (process_heredocs(p, sh) != 0)
	{
		if (g_exit_code)
		{
			g_exit_code = 0;
			sh->last_status = 130;
		}
		return ;
	}
	n = cmd_count(p->cmds);
	if (n <= 1)
		status = run_single(p, p->cmds, sh);
	else
		status = run_pipeline(p, p->cmds, sh, n);
	sh->last_status = status;
}
