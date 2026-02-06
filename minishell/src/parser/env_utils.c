/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:22:02 by sisung            #+#    #+#             */
/*   Updated: 2026/02/02 19:26:29 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	*safe_join(char *s1, char *s2)
{
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

static int	get_key_len(char *env_str)
{
	int	i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	return (i);
}

char	*get_env_value(char *key, t_shell *sh)
{
	int		i;
	int		key_len;

	if (ft_strncmp(key, "?", 2) == 0)
		return (ft_itoa(sh->last_status));
	i = 0;
	while (sh->envp && sh->envp[i])
	{
		key_len = get_key_len(sh->envp[i]);
		if ((int)ft_strlen(key) == key_len && \
			ft_strncmp(key, sh->envp[i], key_len) == 0)
		{
			return (ft_strdup(sh->envp[i] + key_len + 1));
		}
		i++;
	}
	return (ft_strdup(""));
}
