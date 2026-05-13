/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:43:03 by sisung            #+#    #+#             */
/*   Updated: 2026/05/13 14:03:23 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void update_player(t_game *game)
{
	int moved = 0;

	// 여러 키가 동시에 1이면, 이동 함수가 여러 번 불리면서 대각선으로 부드럽게 이동합니다!
	if (game->player.key_w)
	{
		move_forward(game);
		moved = 1; // 이거 때문에 norm이 안맞는데 그냥 지워버릴까?
	}
	if (game->player.key_s)
	{
		move_backward(game);
		moved = 1;
	}
	if (game->player.key_a)
	{
		move_left(game);
		moved = 1;
	}
	if (game->player.key_d)
	{
		move_right(game);
		moved = 1;
	}
	if (game->player.key_left)
	{
		rotate_left(game);
		moved = 1;
	}
	if (game->player.key_right)
	{
		rotate_right(game);
		moved = 1;
	}

	// 이전에 만들었던 Dirty Flag를 여기서 세팅합니다.
	if (moved)
		game->is_moved = 1;
}

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
	// 음수거리 처리
	ray->map_x = (int)floor(player->pos_x);
	ray->map_y = (int)floor(player->pos_y);
	//ray->map_x = (int)player->pos_x;
	//ray->map_y = (int)player->pos_y;
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
//static void	perform_dda(t_ray *ray, t_map *map)
//{
//	// 여기서 나중에 벽 통과할 때는 어떻게 해야할까.
//	while (ray->hit == 0)
//	{
//		// 1. DDA 스텝 이동
//		if (ray->side_dist_x < ray->side_dist_y)
//		{
//			ray->side_dist_x += ray->delta_dist_x;
//			ray->map_x += ray->step_x;
//			ray->side = 0;
//		}
//		else
//		{
//			ray->side_dist_y += ray->delta_dist_y;
//			ray->map_y += ray->step_y;
//			ray->side = 1;
//		}

//		/* 2. 광선이 맵 '밖'을 날아다니는 중입니다.
//			만약 너무 멀리 날아갔다면(예: 50칸 이상) 허공으로 판정하고 루프를 종료합니다. */
//		if (ray->side_dist_x > 1000.0 || ray->side_dist_y > 1000.0)
//		{
//			ray->hit = -1; // 사거리 밖 (허공)
//			break;
//		}

//		// 3. 맵 배열 내부인지 확인 (이탈했다고 광선을 죽이지 않음!)
//		if (ray->map_y >= 0 && ray->map_y < map->height)
//		{
//			// 현재 줄(Y)의 문자열 길이 내부인지 확인
//			if (ray->map_x >= 0 && ray->map_x < (int)ft_strlen(map->grid[ray->map_y]))
//			{
//				// 정상적인 배열 메모리 내부이므로 값을 읽어 벽('1')인지 판별
//				if (map->grid[ray->map_y][ray->map_x] == '1')
//					ray->hit = 1;
//			}
//		}
//		// 만약 위 if문을 통과하지 못했다면?
//		// 그냥 hit=0 인 상태로 while 루프의 처음으로 돌아가 다음 격자로 전진합니다!

//		// 원래 로직
//		//if (map->grid[ray->map_y][ray->map_x] == '1')
//		//	ray->hit = 1;
//	}
//}

/**
 * @brief DDA 루프를 수행하여 벽('1')에 부딪힐 때까지 광선을 전진시킴
 * (부동소수점 무한대 에러 - 중앙 틈새 버그 완벽 수정판)
 */
static void	perform_dda(t_ray *ray, t_map *map)
{
	int	max_steps;

	max_steps = 1000; /* 🚨 실수 거리가 아닌 정수 스텝으로 1000칸 제한 */
	while (ray->hit == 0 && max_steps > 0)
	{
		// 1. DDA 스텝 이동 (INF 값이 들어와도 안전하게 처리됨)
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

		// 2. 맵 배열 내부인지 확인 (배열 밖으로 나가도 죽이지 않고 계속 탐색!)
		if (ray->map_y >= 0 && ray->map_y < map->height)
		{
			if (ray->map_x >= 0 && ray->map_x < (int)ft_strlen(map->grid[ray->map_y]))
			{
				if (map->grid[ray->map_y][ray->map_x] == '1')
					ray->hit = 1; // 진짜 벽을 찾음
			}
		}

		// 3. 한 칸 전진했으므로 카운트 감소
		max_steps--;
	}

	// 4. 1000칸을 전부 탐색했는데도 벽을 못 찾았다면 허공(-1) 처리
	if (max_steps == 0)
		ray->hit = -1;
}

/**
 * @brief 벽까지의 수직 거리와 실제 그려질 높이 계산
 * ?? 만약 이 부분이 없으면 어안 렌즈 보정이 안되서 어안렌즈처럼 보이나?
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
 * @brief 벽의 방향과 텍스처 좌표(tex_x)를 계산
 * @param ray 광선 정보
 * @param player 플레이어 정보
 * @return 텍스처 인덱스 (0:NO, 1:SO, 2:WE, 3:EA)
 */
static int	get_texture_idx(t_ray *ray)
{
	if (ray->side == 0)	// X축 벽 (동/서)
	{
		if (ray->ray_dir_x > 0)
			return (3);	// East
		return (2);		// West
	}
	else // Y축 벽 (남/북)
	{
		if (ray->ray_dir_y > 0)
			return (1);	// South
		return (0);		// North
	}
}

/**
 * @brief 화면의 수직선(세로줄)에 텍스처를 매핑하여 그리는 함수
 *
 * @param game 게임 구조체 포인터
 * @param x 화면에 그릴 수직선의 x 좌표
 * @param ray 광선 정보 구조체 포인터
 * @param tex_idx 매핑할 텍스처 배열의 인덱스 (0: NO, 1: SO, 2: WE, 3: EA)
 * @param tex_x 텍스처 이미지 상에서 읽어올 픽셀의 x 좌표
 */
static void	draw_wall_line(t_game *game, int x, t_ray *ray, int tex_idx, int tex_x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_H / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		// 텍스처 메모리에서 색상 읽기
		color = *(int *)(game->textures[tex_idx].addr +
					(tex_y * game->textures[tex_idx].line_len +
					tex_x * (game->textures[tex_idx].bpp / 8)));
		put_pixel(&game->img, x, y, color);
		y++;
	}
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
	int		tex_idx;
	double	wall_x;
	int		tex_x;

	// 렌더링(DDA) 시작 전에 플레이어 위치부터 최신화!
	update_player(game);
	if (game->is_moved == 0)
		return (0);
	draw_background(game);
	x = 0;
	while (x < SCREEN_W)
	{
		init_ray(x, &ray, &game->player);
		calculate_step(&ray, &game->player);
		perform_dda(&ray, &game->map);

		/* 광선이 진짜 벽에 부딪혔을 때만 벽 렌더링 로직을 수행합니다! */
		if (ray.hit == 1)
		{
			calculate_wall_dims(&ray);

			// 1. 텍스처 방향 및 충돌 지점 계산
			tex_idx = get_texture_idx(&ray);
			if (ray.side == 0)
				wall_x = game->player.pos_y + ray.perp_wall_dist * ray.ray_dir_y;
			else
				wall_x = game->player.pos_x + ray.perp_wall_dist * ray.ray_dir_x;
			wall_x -= floor(wall_x);

			/* 🚨 부동소수점 오차로 인한 텍스처 찢어짐(틈새) 방지 안전장치 */
			if (tex_x >= TEX_WIDTH)
				tex_x = TEX_WIDTH - 1;
			if (tex_x < 0)
				tex_x = 0;

			// 2. 텍스처 x좌표 계산
			tex_x = (int)(wall_x * (double)TEX_WIDTH); // (int), (double) 이런건 왜 해야함?
			if ((ray.side == 0 && ray.ray_dir_x < 0) || (ray.side == 1 && ray.ray_dir_y > 0))
				tex_x = TEX_WIDTH - tex_x - 1;

			// 3. 세로선 그리기
			draw_wall_line(game, x, &ray, tex_idx, tex_x);
		}
		/* 만약 ray.hit == -1 이라면? 아무것도 안 그립니다.
		   즉, 이전에 draw_background에서 칠해둔 지평선(바닥/천장)이 그대로 화면에 남습니다! */
		// ??근데 이렇게 되면 벽일 뚫고 나갔을 때 외부 벽이 안보이지 않나?
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	game->is_moved = 0;
	return (0);
}
