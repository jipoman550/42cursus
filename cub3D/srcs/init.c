#include "cub3d.h"

/**
 * @brief 이미지 버퍼의 (x, y) 좌표에 색상을 기록
 */
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief ESC 키 또는 지원 키 입력 시 호출되는 콜백 (Step 1에서는 ESC만 처리)
 */
static int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit_game(game, 0);
	return (0);
}

/**
 * @brief 창 X 버튼 클릭 시 호출되는 콜백
 */
static int	close_window_handler(t_game *game)
{
	exit_game(game, 0);
	return (0);
}

/**
 * @brief MLX 세션, 윈도우, 이미지 버퍼를 초기화
 */
int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (-1);
	game->win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!game->win)
		return (-1);
	game->img.img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	if (!game->img.img)
		return (-1);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.03;
	return (0);
}

/**
 * @brief 4방향 텍스처 .xpm 파일을 로드
 * textures[0]=NO, [1]=SO, [2]=WE, [3]=EA
 */
int	load_textures(t_game *game)
{
	int	w;
	int	h;

	game->textures[0].img = mlx_xpm_file_to_image(game->mlx,
			game->map.no_path, &w, &h);
	game->textures[1].img = mlx_xpm_file_to_image(game->mlx,
			game->map.so_path, &w, &h);
	game->textures[2].img = mlx_xpm_file_to_image(game->mlx,
			game->map.we_path, &w, &h);
	game->textures[3].img = mlx_xpm_file_to_image(game->mlx,
			game->map.ea_path, &w, &h);
	if (!game->textures[0].img || !game->textures[1].img
		|| !game->textures[2].img || !game->textures[3].img)
	{
		write(2, "Error\nFailed to load textures\n", 30);
		return (-1);
	}
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].img,
			&game->textures[0].bpp, &game->textures[0].line_len,
			&game->textures[0].endian);
	game->textures[1].addr = mlx_get_data_addr(game->textures[1].img,
			&game->textures[1].bpp, &game->textures[1].line_len,
			&game->textures[1].endian);
	game->textures[2].addr = mlx_get_data_addr(game->textures[2].img,
			&game->textures[2].bpp, &game->textures[2].line_len,
			&game->textures[2].endian);
	game->textures[3].addr = mlx_get_data_addr(game->textures[3].img,
			&game->textures[3].bpp, &game->textures[3].line_len,
			&game->textures[3].endian);
	return (0);
}

/**
 * @brief 동적 할당된 모든 자원을 해제
 */
void	free_game(t_game *game)
{
	int	i;

	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
			free(game->map.grid[i++]);
		free(game->map.grid);
	}
	if (game->map.no_path)
		free(game->map.no_path);
	if (game->map.so_path)
		free(game->map.so_path);
	if (game->map.we_path)
		free(game->map.we_path);
	if (game->map.ea_path)
		free(game->map.ea_path);
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

/**
 * @brief 게임 종료: 자원 해제 후 프로세스 종료
 */
void	exit_game(t_game *game, int exit_code)
{
	free_game(game);
	exit(exit_code);
}

/**
 * @brief MLX 이벤트 훅을 등록하고 루프를 시작
 */
void	start_game_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 17, 0, close_window_handler, game);
	mlx_loop(game->mlx);
}
