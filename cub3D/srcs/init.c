/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:42:01 by sisung            #+#    #+#             */
/*   Updated: 2026/05/12 15:51:03 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief MLX 세션, 윈도우, 이미지 버퍼를 초기화
 * @param game 초기화할 게임 구조체 포인터
 * @return 성공 시 0, 실패 시 -1 반환
 */
int	init_game(t_game *game)
{
	// MLX 라이브러리 연결 초기화
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error_and_return(ERR_MLX_INIT));
	// 윈도우 생성 (제목: cub3D)
	game->win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!game->win)
		return (print_error_and_return(ERR_MLX_WIN));
	// 화면에 표시할 메인 이미지 버퍼 생성
	game->img.img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	if (!game->img.img)
		return (print_error_and_return(ERR_MLX_IMG));
	// 이미지 데이터의 메모리 주소 및 정보 가져오기
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	// 플레이어 이동 및 회전 속도 초기값 설정
	game->player.move_speed = 0.009; // 처음값: 0.05
	game->player.rot_speed = 0.003; // 처음값: 0.03
	game->is_moved = 1;
	return (0);
}

/**
 * @brief 4방향 텍스처 .xpm 파일을 로드
 * textures[0]=NO, [1]=SO, [2]=WE, [3]=EA
 * @param game 게임 구조체 포인터
 * @return 모든 텍스처 로드 성공 시 0, 하나라도 실패 시 -1
 */
int	load_textures(t_game *game)
{
	int		w;
	int		h;
	int		i;
	char	*paths[4];

	paths[0] = game->map.no_path;
	paths[1] = game->map.so_path;
	paths[2] = game->map.we_path;
	paths[3] = game->map.ea_path;
	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx, paths[i], &w, &h);
		if (!game->textures[i].img)
			return (print_error_and_return(ERR_MLX_TEX)); // 실패 시 즉시 반환
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bpp, &game->textures[i].line_len,
				&game->textures[i].endian);
		i++;
	}
	return (0);
}

/**
 * @brief 동적 할당된 모든 자원을 해제
 * @param game 해제할 게임 구조체 포인터
 */
void	free_game(t_game *game)
{
	int	i;

	// 맵 그리드(2차원 배열) 메모리 해제
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
			free(game->map.grid[i++]);
		free(game->map.grid);
	}
	// 텍스처 파일 경로 문자열 해제
	if (game->map.no_path)
		free(game->map.no_path);
	if (game->map.so_path)
		free(game->map.so_path);
	if (game->map.we_path)
		free(game->map.we_path);
	if (game->map.ea_path)
		free(game->map.ea_path);
	// 로드된 텍스처 이미지 해제
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	// 메인 이미지 버퍼 해제
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	// 윈도우 파괴
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	// MLX 디스플레이 연결 해제 및 메모리 해제
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

/**
 * @brief 게임 종료: 자원 해제 후 프로세스 종료
 * @param game 게임 구조체 포인터
 * @param exit_code 종료 코드
 */
void	exit_game(t_game *game, int exit_code)
{
	// 모든 자원 해제 후 종료
	free_game(game);
	exit(exit_code);
}

/**
 * @brief MLX 이벤트 훅을 등록하고 루프를 시작
 * input.c에서 정의한 key_press(), close_window() 콜백을 등록
 * @param game 게임 구조체 포인터
 */
void	start_game_loop(t_game *game)
{
	// 키 입력 이벤트(2) 훅 등록 → input.c의 key_press()
	// 2: KeyPress (눌림)
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	// 3: KeyRelease (뗌)
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	// 창 닫기 버튼 이벤트(17) 훅 등록 → input.c의 close_window()
	mlx_hook(game->win, 17, 0, close_window, game);
	// 매 프레임마다 렌더링을 수행하도록 훅 등록
	mlx_loop_hook(game->mlx, render_frame, game);
	// MLX 메인 루프 시작 (이벤트 대기)
	mlx_loop(game->mlx);
}
