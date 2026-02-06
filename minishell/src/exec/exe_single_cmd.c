/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_single_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:48:49 by hama              #+#    #+#             */
/*   Updated: 2026/02/05 20:02:32 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

static void	exe_single_child(t_pipeline *p, t_cmd *cmd, t_shell *sh)
{
	int	status;

	set_signal_dfl();
	if (apply_redirs(cmd->redirs) != 0)
	{
		free_pipeline(p);
		free_envp (sh->envp);
		exit(1);
	}
	if (cmd->is_builtin || is_builtin(cmd->argv[0]))
	{
		status = exe_builtin(p, cmd, sh);
		free_pipeline(p);
		free_envp(sh->envp);
		exit(status);
	}
	status = exe_external(p, cmd, sh);
	free_pipeline(p);
	free_envp(sh->envp);
	exit(status);
}

static	int	run_single_child(t_pipeline *p, t_cmd *cmd, t_shell *sh)
{
	pid_t	pid;
	int		status;

	set_signal_ign();
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		set_signal_interactive();
		return (1);
	}
	if (pid == 0)
		exe_single_child(p, cmd, sh);
	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			break ;
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
	set_signal_interactive();
	return (decode_wait_status(status));
}

int	run_single(t_pipeline *p, t_cmd *cmd, t_shell *sh)
{
	if (is_empty_cmd(cmd))
		return (0);
	if ((cmd->is_builtin || is_builtin(cmd->argv[0]))
		&& is_par_builtin(cmd->argv[0]))
	{
		return (run_single_builtin_in(p, cmd, sh));
	}
	return (run_single_child(p, cmd, sh));
}
