/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 09:59:18 by hama              #+#    #+#             */
/*   Updated: 2026/02/05 19:14:23 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

size_t	key_len(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static int	split_key_value(char *arg, char **key, char **val, int *has_eq)
{
	char	*eq;

	*key = NULL;
	*val = NULL;
	*has_eq = 0;
	if (!arg)
		return (1);
	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		*key = ft_strdup(arg);
		if (!*key)
			return (1);
		else
			return (0);
	}
	*has_eq = 1;
	*key = ft_substr(arg, 0, (size_t)(eq - arg));
	*val = ft_strdup(eq + 1);
	if (!*key || !*val)
		return (free(*key), free(*val), 1);
	return (0);
}

static int	export_key_value(char *argv, t_shell *sh)
{
	char	*key;
	char	*val;
	int		has_eq;
	int		result;

	key = NULL;
	val = NULL;
	has_eq = 0;
	result = 0;
	if (split_key_value(argv, &key, &val, &has_eq) != 0)
		return (free(key), free(val), 1);
	if (!valid_key(key))
		result = print_valid_err("export", argv);
	else if (has_eq == 1)
	{
		if (env_set(&sh->envp, key, val, 1) != 0)
			result = 1;
	}
	else
	{
		if (env_find(sh->envp, key) < 0)
			if (env_set(&sh->envp, key, NULL, 0) != 0)
				result = 1;
	}
	return (free(key), free(val), result);
}

int	ft_export(t_cmd *cmd, t_shell *sh)
{
	int		i;
	int		result;

	if (!sh || !sh->envp)
		return (1);
	if (cmd->argv[0] && !cmd->argv[1])
		export_print(sh->envp);
	result = 0;
	i = 1;
	while (cmd->argv[i])
	{
		if (export_key_value(cmd->argv[i], sh))
			result = 1;
		i++;
	}
	return (result);
}
