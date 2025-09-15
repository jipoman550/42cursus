/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:11:18 by sisung            #+#    #+#             */
/*   Updated: 2025/09/15 15:40:38 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(void)
{
	ft_printf("Error\n");
	exit(1);
}

static void	check_map_elements(char **map, bool	*p, bool *e, size_t *c)
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
				ft_error();
			j++;
		}
		i++;
	}
}

static void	check_map_shape_and_walls(char **map, size_t height, size_t width)
{
	size_t	i;

	if (height <= 2 || width <= 2)
		ft_error();
	i = 0;
	while (i < height)
	{
		if (ft_strlen(map[i]) != width)
			ft_error();
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			ft_error();
		i++;
	}
	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1' || map[height - 1][i] != '1')
			ft_error();
		++i;
	}
}

void	map_validation(char **map)
{
	size_t 	height;
	size_t	width;
	bool	player;
	bool	exit;
	size_t	collectible;

	if (!map || !map[0])
		ft_error();
	player = 0;
	exit = 0;
	collectible = 0;
	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	check_map_shape_and_walls(map, height, width);
	check_map_elements(map, &player, &exit, &collectible);
	if (player != 1 || exit != 1 || collectible < 1)
		ft_error();
	//TODO: BFS/DFS 를 이용한 유효 경로 검사 로직 추가
	check_valid_path(map, collectible);
}
