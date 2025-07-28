/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:32:58 by sisung            #+#    #+#             */
/*   Updated: 2025/07/28 22:26:42 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

static void	free_split(char **sp)
{
	int	i;

	i = 0;
	while (sp[i])
		free(sp[i++]);
	free(sp);
}

static char	*ft_strdup(const char *s)
{
	if (!s)
		return (NULL);

	int		i;
	char	*dup;

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

char	**collect_tokens(int argc, char **argv, int *out_count)
{
	int		total;
	int		i;
	int		j;
	char	**tokens;
	int		idx;
	char	**parts;

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
		free_split(parts);
		i++;
	}
	tokens[idx] = NULL;
	*out_count = total;
	return (tokens);
}
