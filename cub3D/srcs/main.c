/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 23:25:23 by sisung            #+#    #+#             */
/*   Updated: 2026/02/20 03:15:00 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_extension(const char *path, const char *ext)
{
	size_t	path_len;
	size_t	ext_len;

	path_len = ft_strlen(path);
	ext_len = ft_strlen(ext);
	if (path_len < ext_len)
		return (0);
	return (ft_strncmp(path + path_len - ext_len, ext, ext_len + 1) == 0);
}

static void	init_game_struct(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->map.floor_color = -1;
	game->map.ceil_color = -1;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31);
		return (1);
	}
	if (!check_extension(argv[1], ".cub"))
	{
		write(2, "Error\nInvalid file extension (need .cub)\n", 41);
		return (1);
	}
	init_game_struct(&game);
	if (parse_map(argv[1], &game) == -1)
	{
		write(2, "Error\nFailed to parse map\n", 25);
		free_game(&game);
		return (1);
	}
	if (init_game(&game) == -1)
	{
		write(2, "Error\nFailed to initialize MLX\n", 30);
		free_game(&game);
		return (1);
	}
	if (load_textures(&game) == -1)
	{
		free_game(&game);
		return (1);
	}
	start_game_loop(&game);
	return (0);
}