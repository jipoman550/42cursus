/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:33:15 by sisung            #+#    #+#             */
/*   Updated: 2025/10/02 19:52:24 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	get_map_width(char **map)
{
	if (!map || !map[0])
		return (0);
	return (ft_strlen(map[0]));
}

size_t	get_map_height(char **map)
{
	size_t	height;

	if (!map)
		return (0);
	height = 0;
	while (map[height])
		height++;
	return (height);
}

void	find_player_position(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
			{
				game->player_x = j;
				game->player_y = i;
				break ;
			}
			j++;
		}
		i++;
	}
}

int	render_map_return_int(t_game *game)
{
	render_map(game);
	return (0);
}
