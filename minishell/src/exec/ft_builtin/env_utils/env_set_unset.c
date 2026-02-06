/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 09:59:37 by hama              #+#    #+#             */
/*   Updated: 2026/02/05 20:00:04 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

static char	*join_key_value(char *key, char *value, int eq)
{
	char	*tmp;
	char	*result;

	if (!key)
		return (NULL);
	if (eq == 0)
		return (ft_strdup(key));
	else if (!value)
		value = "";
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

static char	**set_new_env_dup(char **envp, int n, char *key_value)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (n + 2));
	if (!new_env)
		return (free(key_value), NULL);
	i = 0;
	while (i < n)
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[i++] = key_value;
	new_env[i] = NULL;
	free(envp);
	return (new_env);
}

int	env_set(char ***p_envp, char *key, char *val, int eq)
{
	char	**envp;
	char	**new_env;
	char	*new_kv;
	int		idx;

	if (!p_envp || !key)
		return (1);
	envp = *p_envp;
	idx = env_find(envp, key);
	new_kv = join_key_value(key, val, eq);
	if (!new_kv)
		return (1);
	if (idx >= 0)
	{
		free(envp[idx]);
		envp[idx] = new_kv;
		return (0);
	}
	new_env = set_new_env_dup(envp, env_len(envp), new_kv);
	if (!new_env)
		return (free(new_kv), 1);
	*p_envp = new_env;
	return (0);
}

static char	**unset_new_env_dup(char **envp, int idx, int n)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(sizeof(char *) * n);
	i = 0;
	j = 0;
	while (i < n)
	{
		if (idx == i)
		{
			free(envp[i]);
			i++;
			continue ;
		}
		new_env[j++] = envp[i++];
	}
	new_env[j] = NULL;
	free(envp);
	return (new_env);
}

int	env_unset(char ***p_envp, char *key)
{
	char	**envp;
	char	**new_env;
	int		idx;

	envp = *p_envp;
	idx = env_find(envp, key);
	if (idx < 0)
		return (0);
	new_env = unset_new_env_dup(envp, idx, env_len(envp));
	*p_envp = new_env;
	return (0);
}
