/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:51:30 by sisung            #+#    #+#             */
/*   Updated: 2025/09/15 18:17:10 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**map_copy_duplicate_fail(char **map_copy, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(map_copy[j]);
		j++;
	}
	free(map_copy);
	return (NULL);
}

static char	**copy_map(char **map)
{
	char	**map_copy;
	size_t	i;

	i = 0;
	while (map[i])
	i++;
	map_copy = malloc(sizeof(char *) * (i + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
			return (map_copy_duplicate_fail(map_copy, i));
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

void	check_valid_path(char **map, size_t total_c)
{
	char	**map_copy;

	map_copy = copy_map(map);
	if (!map_copy)
		ft_error();
}
