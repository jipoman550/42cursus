/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:20:48 by sisung            #+#    #+#             */
/*   Updated: 2026/02/02 19:19:01 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
			c == '\v' || c == '\f' || c == '\r');
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
}

int	is_metachar(char c)
{
	if (ft_isspace(c) || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
