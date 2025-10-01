/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:32:26 by sisung            #+#    #+#             */
/*   Updated: 2025/10/01 17:42:41 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_exit(t_game *game)
{
	ft_cleanup_resources(game);
	exit(0);
	return (0);
}

int	handle_keypress(int	keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_exit(game);
	else if (keycode == KEY_W || keycode == KEY_A
			|| keycode == KEY_S || keycode == KEY_D)
	{
		// 플레이어 이동 로직 호출
		move_player(game, keycode);
	}
	// ft_printf("Keycode: %d\n", keycode); // 디버깅용
	return (0);
}
