/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:51:47 by sisung            #+#    #+#             */
/*   Updated: 2026/02/04 20:32:55 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_valid_env(char c)
{
	return (ft_isalnum(c) || c == '_');
}

void	update_quote_status(char c, char *quote)
{
	if (*quote == 0 && (c == '\'' || c == '\"'))
		*quote = c;
	else if (*quote != 0 && c == *quote)
		*quote = 0;
}

int	is_expandable(char *str, int i, char quote)
{
	if (str[i] == '$' && quote != '\'')
	{
		if (str[i + 1] && !ft_isspace(str[i + 1]) \
			&& str[i + 1] != '\"' && str[i + 1] != '\'')
			return (1);
	}
	return (0);
}

int	is_tilde_exp(char *str, int i, char quote)
{
	return (str[i] == '~' && quote == 0 && i == 0
		&& (str[i + 1] == '\0' || str[i + 1] == '/'));
}
