/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 09:59:34 by hama              #+#    #+#             */
/*   Updated: 2026/02/03 15:23:08 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

char	**env_dup(char **envp)
{
	char	**copy_envp;
	int		n;
	int		i;

	n = env_len(envp);
	copy_envp = malloc(sizeof(char *) * (n + 1));
	if (!copy_envp)
		return (NULL);
	i = 0;
	while (i < n)
	{
		copy_envp[i] = ft_strdup(envp[i]);
		if (!copy_envp[i])
		{
			env_free(copy_envp, i);
			return (NULL);
		}
		i++;
	}
	copy_envp[i] = NULL;
	return (copy_envp);
}

void	env_free(char **envp, int flag)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	if (flag < 0)
	{
		while (envp[i])
			free(envp[i++]);
		free(envp);
	}
	else
	{
		while (i < flag)
			free(envp[i++]);
		free(envp);
	}
}
