/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:10:51 by sisung            #+#    #+#             */
/*   Updated: 2025/10/02 15:01:35 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	game;
	char	*file_name;

	ft_bzero(&game, sizeof(t_game));

	if (argc != 2)
		ft_error(&game, "more than 2 argument.");
	file_name = argv[1];
	if (ft_strlen(file_name) < 4
		|| ft_strncmp(file_name + ft_strlen(file_name) - 4, ".ber", 4) != 0)
		ft_error(&game, "file name is not correct.");
	game.map = parse_map(argv[1]);
	if (!game.map)
		ft_error(&game, "failed parsing map.");
	if (!map_validation(game.map))
		ft_error(&game, "invalid map.");
// ------------------------------------------
	game.mlx = mlx_init();
	if (!game.mlx)
		ft_error(&game, "MiniLibX initialization failed.");

	game.win_width = get_map_width(game.map) * TILE_SIZE;
	game.win_height = get_map_height(game.map) * TILE_SIZE;

	game.win = mlx_new_window(game.mlx, game.win_width, game.win_height, "so_long");
	if (!game.win)
		ft_error(&game, "MiniLibX new window generation failed.");

	load_images(&game);

	render_map(&game);

	mlx_key_hook(game.win, handle_keypress, &game);

	mlx_hook(game.win, 17, 0, handle_exit, &game);

	mlx_hook(game.win, 9, 0, render_map_return_int, &game);

	mlx_loop(game.mlx);

	// 게임 루프 시작

	// 정리 (정상 종료 시)

	return (0);
}
