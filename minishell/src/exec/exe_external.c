/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_external.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 09:59:05 by hama              #+#    #+#             */
/*   Updated: 2026/07/07 12:25:53 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

void	free_split_hama(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	not_exist_path(t_cmd *cmd, t_pipeline *p, t_shell *sh)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	free_pipeline(p);
	free_envp(sh->envp);
	exit(127);
}

static char	*make_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

static char	*resolve_path(t_cmd *cmd, t_pipeline *p, t_shell *sh)
{
	char	**all_path;
	char	*env_path;
	char	*path;
	int		i;

	env_path = env_get(sh->envp, "PATH");
	if (!env_path)
	{
		not_exist_path(cmd, p, sh);
		return (NULL);
	}
	all_path = ft_split(env_path, ':');
	if (!all_path)
		return (NULL);
	i = 0;
	while (all_path[i])
	{
		path = make_path(all_path[i], cmd->argv[0]);
		if (path && access(path, X_OK) == 0)
			return (free_split_hama(all_path), path);
		free(path);
		i++;
	}
	free_split_hama(all_path);
	return (NULL);
}

int	exe_external(t_pipeline *p, t_cmd *cmd, t_shell *sh)
{
	char	*path;

	if (ft_strchr(cmd->argv[0], '/') != NULL)
	{
		execve(cmd->argv[0], cmd->argv, sh->envp);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd->argv[0]);
		free_pipeline(p);
		free_envp(sh->envp);
		exit(127);
	}
	path = resolve_path(cmd, p, sh);
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free_pipeline(p);
		free_envp(sh->envp);
		exit(127);
	}
	execve(path, cmd->argv, sh->envp);
	perror (cmd->argv[0]);
	free(path);
	return (126);
}
