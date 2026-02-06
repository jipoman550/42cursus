/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:09:42 by sisung            #+#    #+#             */
/*   Updated: 2026/02/04 21:04:22 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	handle_env_var(char *str, int *i, char **res, t_shell *sh)
{
	int		start;
	char	*key;
	char	*val;

	(*i)++;
	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		key = ft_strdup("?");
	}
	else
	{
		while (str[*i] && is_valid_env(str[*i]))
			(*i)++;
		key = ft_substr(str, start, *i - start);
	}
	val = get_env_value(key, sh);
	*res = safe_join(*res, val);
	free(key);
	free(val);
}

static void	append_normal_str(char *str, int start, int end, char **res)
{
	char	*chunk;

	if (start == end)
		return ;
	chunk = ft_substr(str, start, end - start);
	*res = safe_join(*res, chunk);
	free(chunk);
}

static void	handle_tilde(char **res, int *i, int *start, t_shell *sh)
{
	char	*home;

	home = get_env_value("HOME", sh);
	if (!home)
		home = ft_strdup("");
	*res = safe_join(*res, home);
	free(home);
	*start = *i + 1;
}

char	*expand_str(char *str, t_shell *sh)
{
	char	*res;
	char	quote;
	int		i;
	int		start;

	res = ft_strdup("");
	quote = 0;
	i = -1;
	start = 0;
	while (str[++i])
	{
		update_quote_status(str[i], &quote);
		if (is_tilde_exp(str, i, quote))
			handle_tilde(&res, &i, &start, sh);
		else if (is_expandable(str, i, quote))
		{
			append_normal_str(str, start, i, &res);
			handle_env_var(str, &i, &res, sh);
			start = i--;
		}
	}
	append_normal_str(str, start, i, &res);
	return (res);
}
