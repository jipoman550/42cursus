/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:55:39 by hama              #+#    #+#             */
/*   Updated: 2026/02/04 13:59:00 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

int	err_p_f(pid_t *pid, int i, int prev, int pipefd[2])
{
	close_fd(pipefd);
	if (prev != -1)
		close(prev);
	wait_prev_child(pid, i);
	free(pid);
	return (1);
}

void	pipe_clean_up(t_pipeline *p, t_shell *sh, pid_t *pid, int s)
{
	free_envp(sh->envp);
	free_pipeline(p);
	free(pid);
	exit(s);
}

void	close_fd(int pipe_fd[2])
{
	if (pipe_fd[0] >= 0)
	{
		close(pipe_fd[0]);
		pipe_fd[0] = -1;
	}
	if (pipe_fd[1] >= 0)
	{
		close(pipe_fd[1]);
		pipe_fd[1] = -1;
	}
}

int	set_std_inout(int i, int n, t_mix m, t_cmd *cmd)
{
	if (m.prev != -1)
	{
		if (dup2(m.prev, STDIN_FILENO) < 0)
			return (perror("dup2"), 1);
	}
	if (i != n - 1)
	{
		if (dup2(m.pipefd[1], STDOUT_FILENO) < 0)
			return (perror("dup2"), 1);
	}
	if (m.pipefd[0] >= 0)
		close(m.pipefd[0]);
	if (m.pipefd[1] >= 0)
		close(m.pipefd[1]);
	if (apply_redirs(cmd->redirs) != 0)
		return (1);
	return (0);
}

void	wait_prev_child(pid_t *pid, int count)
{
	int	status;
	int	j;

	j = 0;
	while (j < count)
	{
		if (pid[j] > 0)
			waitpid(pid[j], &status, 0);
		j++;
	}
}
