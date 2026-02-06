/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 09:59:27 by hama              #+#    #+#             */
/*   Updated: 2026/02/05 19:26:07 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

static int	has_equal(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	ft_env(t_pipeline *p, t_cmd *cmd, t_shell *sh)
{
	int		i;
	t_cmd	tmp;

	if (!sh || !sh->envp)
		return (1);
	if (cmd && cmd->argv && cmd->argv[1])
	{
		ft_bzero(&tmp, sizeof(t_cmd));
		tmp.argv = &cmd->argv[1];
		return (exe_external(p, &tmp, sh));
	}
	i = 0;
	while (sh->envp[i])
	{
		if (has_equal(sh->envp[i]))
		{
			write (STDOUT_FILENO, sh->envp[i], ft_strlen(sh->envp[i]));
			write (STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
	return (0);
}
