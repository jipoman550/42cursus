/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 09:59:39 by hama              #+#    #+#             */
/*   Updated: 2026/02/03 15:23:31 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

int	env_len(char **envp)
{
	int	i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static int	key_match(char *env, char *key)
{
	int	key_len;

	if (!env || !key)
		return (0);
	key_len = (int)ft_strlen(key);
	if (ft_strncmp(env, key, key_len) != 0)
		return (0);
	if (env[key_len] == '=' || env[key_len] == '\0')
		return (1);
	return (0);
}

int	env_find(char **envp, char *key)
{
	int	i;

	if (!envp || !key)
		return (-1);
	i = 0;
	while (envp[i])
	{
		if (key_match(envp[i], key))
			return (i);
		i++;
	}
	return (-1);
}

char	*env_get(char **envp, char *key)
{
	int	idx;
	int	key_len;

	idx = env_find(envp, key);
	if (idx < 0)
		return (NULL);
	key_len = (int)ft_strlen(key);
	return (envp[idx] + key_len + 1);
}
