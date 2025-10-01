/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:17:29 by sisung            #+#    #+#             */
/*   Updated: 2025/10/01 12:56:23 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*load_xpm(t_game *game, const char *path)
{
	void	*img_ptr;
	size_t	size;

	size = TILE_SIZE;
	img_ptr = mlx_xpm_file_to_image(game->mlx, (char *)path, &size, &size);
	if (!img_ptr)
		ft_error(game, "failed to load image file.");
	return (img_ptr);
}

void	load_images(t_game *game)
{
	game->img_wall = load_xpm(game, WALL_PATH);
	game->img_floor = load_xpm(game, FLOOR_PATH);
	game->img_exit = load_xpm(game, EXIT_PATH);
	game->img_collect = load_xpm(game, COLLECT_PATH);
	game->img_player_right = load_xpm(game, PLAYER_RIGHT_PATH);
	game->img_player_left = load_xpm(game, PLAYER_LEFT_PATH);
	game->img_player_up = load_xpm(game, PLAYER_UP_PATH);
	game->img_player_down = load_xpm(game, PLAYER_DOWN_PATH);
	game->player_direction = KEY_S;
}
