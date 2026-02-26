/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:43:03 by sisung            #+#    #+#             */
/*   Updated: 2026/02/26 10:43:04 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief 현재 x 좌표에 대한 광선(Ray) 정보를 초기화
 * @param x 현재 화면의 세로선 좌표
 * @param ray 광선 정보 구조체
 * @param player 플레이어 정보 구조체
 */
static void	init_ray(int x, t_ray *ray, t_player *player)
{
	ray->camera_x = 2 * x / (double)SCREEN_W - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

/**
 * @brief DDA를 시작하기 전 거리 및 단계(Step) 계산
 */
static void	calculate_step(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
}

/**
 * @brief DDA 루프를 수행하여 벽('1')에 부딪힐 때까지 광선을 전진시킴
 */
static void	perform_dda(t_ray *ray, t_map *map)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

/**
 * @brief 벽까지의 수직 거리와 실제 그려질 높이 계산
 */
static void	calculate_wall_dims(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(SCREEN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_H / 2;
	if (ray->draw_end >= SCREEN_H)
		ray->draw_end = SCREEN_H - 1;
}

/**
 * @brief 매 프레임마다 호출되어 화면을 렌더링하는 메인 함수
 * @param game 게임 구조체 포인터
 * @return 0
 */
int	render_frame(t_game *game)
{
	int		x;
	t_ray	ray;
	int		color;

	// 1. 천장과 바닥 먼저 그리기
	draw_background(game);
	// 2. 각 세로선마다 레이캐스팅 수행
	x = 0;
	while (x < SCREEN_W)
	{
		init_ray(x, &ray, &game->player);
		calculate_step(&ray, &game->player);
		perform_dda(&ray, &game->map);
		calculate_wall_dims(&ray);
		// 단색 벽 색상 결정 (X축/Y축 부딪힘에 따라 음영 조절)
		if (ray.side == 0)
			color = 0xCCCCCC; // 밝은 회색
		else
			color = 0x999999; // 어두운 회색
		// 세로선 그리기
		int y = ray.draw_start;
		while (y < ray.draw_end)
		{
			put_pixel(&game->img, x, y, color);
			y++;
		}
		x++;
	}
	// 3. 만들어진 이미지를 윈도우에 출력
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
