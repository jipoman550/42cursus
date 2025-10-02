/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:52:48 by sisung            #+#    #+#             */
/*   Updated: 2025/10/02 17:18:30 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_player_position(t_game *game, int new_x, int new_y, int keycode)
{
	char	next_tile;

	next_tile = game->map[new_y][new_x];
	if (game->map[game->player_y][game->player_x] != 'E')
		game->map[game->player_y][game->player_x] = '0';
	if (next_tile == 'C')
	{
		game->collectables--;
		game->map[new_y][new_x] = '0';
	}
	else if (next_tile == 'E')
	{
		if (game->collectables == 0)
			handle_exit(game);
	}
	game->player_x = new_x;
	game->player_y = new_y;
	game->player_direction = keycode;
	if (game->map[new_y][new_x] != 'E')
		game->map[new_y][new_x] = 'P';
	render_map(game);
}

void	move_player(t_game *game, int keycode)
{
	int	next_x;
	int	next_y;

	next_x = game->player_x;
	next_y = game->player_y;
	if (keycode == KEY_W)
		next_y--;
	else if (keycode == KEY_S)
		next_y++;
	else if (keycode == KEY_A)
		next_x--;
	else if (keycode == KEY_D)
		next_x++;
	if (game->map[next_y][next_x] != '1')
	{
		update_player_position(game, next_x, next_y, keycode);
		game->moves++;
		ft_printf("Moves: %d\n", game->moves); // 디버깅용
	}
}
