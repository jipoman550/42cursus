/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:11:18 by sisung            #+#    #+#             */
/*   Updated: 2025/09/29 16:17:48 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	check_map_elements(char **map, size_t	*p, size_t *e, size_t *c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				(*p)++;
			else if (map[i][j] == 'E')
				(*e)++;
			else if (map[i][j] == 'C')
				(*c)++;
			else if (map[i][j] != '0' && map[i][j] != '1')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static bool	check_map_shape_and_walls(char **map, size_t height, size_t width)
{
	size_t	i;

	if (height <= 2 || width <= 2)
		return (false);
	i = 0;
	while (i < height)
	{
		if (ft_strlen(map[i]) != width)
			return (false);
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (false);
		i++;
	}
	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1' || map[height - 1][i] != '1')
			return (false);
		++i;
	}
	return (true);
}

bool	map_validation(char **map)
{
	size_t	height;
	size_t	width;
	size_t	player;
	size_t	exit;
	size_t	collectible;

	if (!map || !map[0])
		return (false);
	player = 0;
	exit = 0;
	collectible = 0;
	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	if (!check_map_shape_and_walls(map, height, width))
		return (false);
	if (!check_map_elements(map, &player, &exit, &collectible))
		return (false);
	if (player != 1 || exit != 1 || collectible < 1)
		return (false);
	if (!check_valid_path(map, collectible))
		return (false);
	return (true);
}
