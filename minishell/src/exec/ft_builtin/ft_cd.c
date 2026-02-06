/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 09:59:31 by hama              #+#    #+#             */
/*   Updated: 2026/02/04 21:49:55 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

static char	*get_cwd(void)
{
	char	buf[PATH_MAX];

	if (!getcwd(buf, sizeof(buf)))
		return (NULL);
	return (ft_strdup(buf));
}

static int	update_pwd(t_shell *sh, char *flag)
{
	char	*cwd;

	cwd = get_cwd();
	if (!cwd)
		return (1);
	env_set(&sh->envp, flag, cwd, 1);
	free(cwd);
	return (0);
}

static char	*get_cd_target(t_cmd *cmd, t_shell *sh)
{
	if (!cmd->argv[1])
		return (env_get(sh->envp, "HOME"));
	else if (!ft_strcmp(cmd->argv[1], "-"))
		return (env_get(sh->envp, "OLDPWD"));
	return (cmd->argv[1]);
}

static int	is_arg_check(t_cmd *cmd)
{
	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd(cmd->argv[2], STDERR_FILENO);
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	ft_cd(t_cmd *cmd, t_shell *sh)
{
	char	*target;
	char	*oldpwd;

	if (!sh || !sh->envp)
		return (1);
	if (is_arg_check(cmd))
		return (1);
	target = get_cd_target(cmd, sh);
	if (!target)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	oldpwd = get_cwd();
	if (!oldpwd)
		return (perror("minishell: cd"), 1);
	if (chdir(target) != 0)
		return (perror("minishell: cd"), free(oldpwd), 1);
	env_set(&sh->envp, "OLDPWD", oldpwd, 1);
	free(oldpwd);
	if (update_pwd(sh, "PWD"))
		return (1);
	return (0);
}
