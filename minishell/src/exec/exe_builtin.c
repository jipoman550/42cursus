/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:32:12 by hama              #+#    #+#             */
/*   Updated: 2026/02/04 00:23:39 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

static int	stdio_backup(int *save_in, int *save_out)
{
	*save_in = dup(STDIN_FILENO);
	if (*save_in < 0)
		return (perror("dup_blt"), 1);
	*save_out = dup(STDOUT_FILENO);
	if (*save_out < 0)
	{
		perror("dup_blt");
		close(*save_in);
		*save_in = -1;
	}
	return (0);
}

static void	stdio_restore(int save_in, int save_out)
{
	if (save_in >= 0)
	{
		dup2(save_in, STDIN_FILENO);
		close(save_in);
	}
	if (save_out >= 0)
	{
		dup2(save_out, STDOUT_FILENO);
		close(save_out);
	}
}

int	exe_builtin(t_pipeline *p, t_cmd *cmd, t_shell *sh)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (ft_echo(cmd));
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (ft_pwd(cmd));
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (ft_env(p, cmd, sh));
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		return (ft_cd(cmd, sh));
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (ft_export(cmd, sh));
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (ft_unset(cmd, sh));
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (ft_exit(cmd, sh));
	return (1);
}

int	run_single_builtin_in(t_pipeline *p, t_cmd *cmd, t_shell *sh)
{
	int	save_in;
	int	save_out;
	int	rc;

	if (stdio_backup(&save_in, &save_out) != 0)
		return (1);
	if (apply_redirs(cmd->redirs) != 0)
	{
		stdio_restore(save_in, save_out);
		return (1);
	}
	rc = exe_builtin(p, cmd, sh);
	stdio_restore(save_in, save_out);
	return (rc);
}
