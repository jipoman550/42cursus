/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:17:29 by sisung            #+#    #+#             */
/*   Updated: 2025/10/02 18:38:27 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*load_xpm(t_game *game, const char *path)
{
	void	*img_ptr;
	int		size;

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
	game->img_c = load_xpm(game, COLLECT_PATH);
	game->img_player_right = load_xpm(game, PLAYER_RIGHT_PATH);
	game->img_player_left = load_xpm(game, PLAYER_LEFT_PATH);
	game->img_player_up = load_xpm(game, PLAYER_UP_PATH);
	game->img_player_down = load_xpm(game, PLAYER_DOWN_PATH);
	game->player_direction = KEY_S;
}

static void	*p_image(t_game *game)
{
	if (game->player_direction == KEY_W)
		return (game->img_player_up);
	else if (game->player_direction == KEY_A)
		return (game->img_player_left);
	else if (game->player_direction == KEY_D)
		return (game->img_player_right);
	else
		return (game->img_player_down);
}

static void	put_tile(t_game *game, size_t x, size_t y)
{
	char	tile;
	int		px;
	int		py;

	tile = game->map[y][x];
	px = x * TILE_SIZE;
	py = y * TILE_SIZE;
	if (tile != '1')
		mlx_put_image_to_window(game->mlx, game->win, game->img_floor, px, py);
	if (tile == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->img_wall, px, py);
	else if (tile == 'P')
		mlx_put_image_to_window(game->mlx, game->win, p_image(game), px, py);
	else if (tile == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->img_c, px, py);
	else if (tile == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->img_exit, px, py);
}

void	render_map(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			put_tile(game, x, y);
			x++;
		}
		y++;
	}
}
