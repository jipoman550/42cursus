/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:17:41 by sisung            #+#    #+#             */
/*   Updated: 2026/02/02 19:27:09 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	char	quote;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	quote = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			new_str[j++] = str[i];
		i++;
	}
	return (new_str);
}
