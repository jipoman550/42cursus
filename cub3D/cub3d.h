/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 23:25:31 by sisung            #+#    #+#             */
/*   Updated: 2026/05/04 09:26:16 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include <string.h>

# include "libft2.h"

# define SCREEN_W 1280
# define SCREEN_H 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

/**
 * @brief MiniLibX 이미지 정보를 담는 구조체
 * @param img MiniLibX가 생성한 이미지 포인터
 * @param addr 이미지의 메모리 주소 (픽셀 데이터 시작점)
 * @param bpp 픽셀 당 비트 수 (bits per pixel)
 * @param line_len 한 줄의 바이트 수
 * @param endian 엔디안 (0: Little Endian, 1: Big Endian)
 */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

/**
 * @brief 맵 파싱 정보를 담는 구조체
 * @param grid 맵의 2차원 배열
 * @param width 맵의 최대 너비
 * @param height 맵의 높이
 * @param no_path, so_path, we_path, ea_path 각 방향의 텍스처 파일 경로
 * @param floor_color, ceil_color 바닥과 천장의 RGB 색상 값 (int로 압축)
 */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceil_color;
}	t_map;

/**
 * @brief 플레이어의 상태 정보를 담는 구조체
 * @param pos_x, pos_y 플레이어의 현재 위치 (맵 좌표)
 * @param dir_x, dir_y 플레이어가 바라보는 방향 벡터
 * @param plane_x, plane_y 카메라 평면 벡터 (방향 벡터에 수직)
 * @param move_speed 이동 속도
 * @param rot_speed 회전 속도
 */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

/**
 * @brief 레이캐스팅 계산에 필요한 변수들을 담는 구조체
 * @param camera_x 현재 x좌표에 해당하는 카메라 평면 상의 비율 (-1 ~ 1)
 * @param ray_dir_x, ray_dir_y 현재 광선의 방향 벡터
 * @param map_x, map_y 광선이 위치한 현재 맵의 격자 좌표
 * @param side_dist_x, side_dist_y 현재 위치에서 다음 x, y축 격자선까지의 거리
 * @param delta_dist_x, delta_dist_y 광선이 x, y축으로 한 칸 이동하는 데 필요한 거리
 * @param perp_wall_dist 어안 렌즈 효과를 보정한, 플레이어로부터 벽까지의 수직 거리
 * @param step_x, step_y 광선이 진행하는 방향 (x, y 각각 +1 또는 -1)
 * @param hit 벽 충돌 여부 (0: 미충돌, 1: 충돌)
 * @param side 어느 축의 벽에 부딪혔는지 (0: X축, 1: Y축)
 * @param line_height 화면에 그려야 할 벽의 높이 (픽셀 단위)
 * @param draw_start, draw_end 벽 그리기를 시작하고 끝낼 y좌표
 */
typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

/**
 * @brief 게임의 모든 주요 데이터들을 담는 최상위 구조체
 * @param mlx MiniLibX 세션 포인터
 * @param win MiniLibX 윈도우 포인터
 * @param img 화면에 최종적으로 출력될 이미지를 관리하는 구조체
 * @param map 맵 정보
 * @param player 플레이어 정보
 * @param textures 각 방향(NO, SO, WE, EA)의 텍스처 이미지를 담는 배열
 */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map;
	t_player	player;
	t_img		textures[4];
}	t_game;

int		parse_map(const char *file_path, t_game *game);
int		init_game(t_game *game);
int		load_textures(t_game *game);
void	free_game(t_game *game);
void	exit_game(t_game *game, int exit_code);
void	start_game_loop(t_game *game);
void	put_pixel(t_img *img, int x, int y, int color);
int		parse_color(int *color_field, const char *rgb_str);
void	free_split(char **tokens);
int		check_extension(const char *path, const char *ext);

/* srcs/render_utils.c — 렌더링 유틸리티 */
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_background(t_game *game);

/* srcs/raycasting.c — 레이캐스팅 및 렌더링 메인 */
int		render_frame(t_game *game);

/* srcs/input.c — 키 입력 및 플레이어 이동 */
int		key_press(int keycode, t_game *game);
int		close_window(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

#endif