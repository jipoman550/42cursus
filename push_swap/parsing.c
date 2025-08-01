/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:32:58 by sisung            #+#    #+#             */
/*   Updated: 2025/08/01 18:15:04 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

static size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	if (!s)
		return (0);
	cnt = 0;
	while (*s)
	{
		cnt++;
		s++;
	}
	return (cnt);
}

static char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup;

	if (!s)
		return (NULL);
	dup = (char *)malloc(ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	**parts_to_tokens(int argc, char **argv, char **tokens)
{
	size_t	idx;
	int		i;
	size_t	j;
	char	**parts;

	idx = 0;
	i = 1;
	while (i < argc)
	{
		parts = ft_split(argv[i], ' ');
		if (!parts)
			ft_error();
		j = 0;
		while (parts[j])
			tokens[idx++] = ft_strdup(parts[j++]);
		free_str_array(parts);
		i++;
	}
	tokens[idx] = NULL;
	return (tokens);
}

char	**collect_tokens(int argc, char **argv, size_t *out_count)
{
	size_t	total;
	int		i;
	char	**tokens;

	total = 0;
	i = 1;
	while (i < argc)
	{
		total += count_words(argv[i], ' ');
		i++;
	}
	tokens = malloc(sizeof(char *) * (total + 1));
	if (!tokens)
		ft_error();
	*out_count = total;
	return (parts_to_tokens(argc, argv, tokens));
}
