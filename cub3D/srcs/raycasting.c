/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:43:03 by sisung            #+#    #+#             */
/*   Updated: 2026/05/20 17:15:09 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void update_player(t_game *game)
{
	// 여러 키가 동시에 1이면, 이동 함수가 여러 번 불리면서 대각선으로 부드럽게 이동합니다!
	if (game->player.key_w)
		move_forward(game);
	if (game->player.key_s)
		move_backward(game);
	if (game->player.key_a)
		move_left(game);
	if (game->player.key_d)
		move_right(game);
	if (game->player.key_left)
		rotate_left(game);
	if (game->player.key_right)
		rotate_right(game);

	// 이전에 만들었던 Dirty Flag를 여기서 세팅합니다.
	if (game->player.key_w || game->player.key_s || game->player.key_a
		|| game->player.key_d || game->player.key_left || game->player.key_right)
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
 * 어안렌즈 현상을 방지하고, 화면에 그릴 벽의 시작점과 끝점을 구합니다.
 */
static void	calculate_wall_dims(t_ray *ray)
{
	// 1. 수직 거리(Perpendicular Distance) 계산
	// ray->side == 0은 광선이 X축 격자선(세로선) 즉, 동/서쪽 벽에 부딪혔음을 의미합니다.
	if (ray->side == 0)
		// DDA 루프는 벽을 '발견'하는 순간 이미 벽 안쪽으로 1스텝(delta_dist)을
		// 밟아버린 상태로 종료됩니다. 따라서 마지막에 더했던 1스텝(delta_dist_x)을
		// 다시 빼주어야 정확히 벽 '표면'까지의 거리가 나옵니다.
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	// ray->side == 1은 광선이 Y축 격자선(가로선) 즉, 남/북쪽 벽에 부딪혔음을 의미합니다.
	else
		// 위와 동일한 원리로 Y축 방향의 마지막 1스텝을 빼줍니다.
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	// 2. 모니터에 그릴 벽의 픽셀 높이(line_height) 계산
	// 거리가 멀면 벽이 작게, 가까우면 크게 보여야 합니다. (반비례 관계)
	// 모니터 세로 해상도(SCREEN_H)를 수직 거리로 나누어 실제 픽셀 높이를 구합니다.
	ray->line_height = (int)(SCREEN_H / ray->perp_wall_dist);
	// 3. 화면에서 벽을 그리기 시작할 Y 좌표(draw_start) 계산
	// 화면의 정중앙(SCREEN_H / 2)을 기준으로,
	// 계산된 벽 높이의 절반(-line_height / 2)만큼 위로 올라간 곳이 시작점입니다.
	ray->draw_start = -ray->line_height / 2 + SCREEN_H / 2;
	// 만약 벽이 너무 가까워서 화면 천장(0)을 뚫고 올라갔다면,
	// 그리기 시작점을 화면의 맨 위인 0으로 고정(Clamping)하여 화면 밖 메모리 침범을 막습니다.
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	// 4. 화면에서 벽 그리기를 끝낼 Y 좌표(draw_end) 계산
	// 화면의 정중앙(SCREEN_H / 2)을 기준으로,
	// 계산된 벽 높이의 절반(line_height / 2)만큼 아래로 내려간 곳이 끝점입니다.
	ray->draw_end = ray->line_height / 2 + SCREEN_H / 2;
	// 만약 벽이 너무 가까워서 화면 바닥(SCREEN_H)을 뚫고 내려갔다면,
	// 그리기 끝점을 화면의 맨 아래인 SCREEN_H - 1로 고정하여 에러를 막습니다.
	if (ray->draw_end >= SCREEN_H)
		ray->draw_end = SCREEN_H;
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
	double	step;		// 모니터 1픽셀을 칠할 때, 텍스처 이미지를 몇 픽셀 건너뛸지(보폭)
	double	tex_pos;	// 원본 텍스처 이미지 상의 정확한 Y 실수 좌표
	int		y;			// 모니터의 Y 좌표 (화면 위에서 아래로 스캔)
	int		tex_y;		// tex_pos를 정수로 바꾼 진짜 텍스처 Y 인덱스 번호
	int		color;		// 텍스처에서 뜯어온 픽셀 1개의 색상값

	// 1. 텍스처 팽창/압축 보폭(step) 계산
	// 예: 텍스처(64)를 모니터(128)에 늘려 그릴 때 -> step = 0.5 (텍스처를 0.5씩 천천히 읽음)
	// 예: 텍스처(64)를 모니터(32)에 줄여 그릴 때 -> step = 2.0 (텍스처를 2칸씩 띄엄띄엄 읽음)
	step = 1.0 * TEX_HEIGHT / ray->line_height;
	// 2. 텍스처 읽기 시작점(tex_pos) 계산 (벽이 화면 위로 뚫고 나갔을 때를 대비한 보정)
	// 만약 벽이 너무 가까워서 모니터 밖으로 잘렸다면, 텍스처의 0번(맨 위)부터 읽으면 안 됩니다!
	// 잘려나간 만큼 텍스처도 중간부터 읽기 시작하도록 시작점을 0보다 큰 값으로 당겨줍니다.
	tex_pos = (ray->draw_start - SCREEN_H / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		// 3. 텍스처 Y 인덱스 추출 및 오버플로우 방지 (비트 연산 마법)
		// (int)로 소수점을 버리고 정수로 만듭니다.
		// & (TEX_HEIGHT - 1) 은 비트 마스킹 기법으로, tex_y가 64(TEX_HEIGHT)를 넘어갈 경우
		// 강제로 63 이하로 묶어버려 Out of Bounds(Segfault)를 방지하는 극한의 최적화입니다.
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		// 다음 모니터 픽셀을 위해 텍스처 좌표도 보폭(step)만큼 전진
		tex_pos += step;
		// 4. MLX 이미지 메모리에서 픽셀 색상값 직접 뜯어오기
		// 1차원 배열로 된 이미지 메모리에서 2차원(x, y) 좌표를 찾는 공식: (y * 너비) + x
		color = *(int *)(game->textures[tex_idx].addr +
					(tex_y * game->textures[tex_idx].line_len +
					tex_x * (game->textures[tex_idx].bpp / 8)));
		// 5. 찾아낸 색상을 내 모니터 이미지 버퍼에 그리기
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
	ft_memset(&ray, 0, sizeof(t_ray));
	tex_x = 0;
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
			// 광선이 부딪힌 면(동/서/남/북)을 판별하여 4개의 텍스처 중 어느 이미지를 쓸지 고릅니다.
			tex_idx = get_texture_idx(&ray);
			// ray.side == 0은 광선이 X축 모눈종이 선(동쪽 또는 서쪽을 바라보는 벽)에 맞았음을 의미합니다.
			if (ray.side == 0)
				// 🚨 핵심: X축 벽에 맞았다는 건, 벽이 화면상에서 세로로 길게 서 있다는 뜻입니다.
				// 벽 표면의 어디에 맞았는지 알려면 광선의 정확한 'Y좌표' 도착점을 구해야 합니다!
				// 공식: 도착점 = 시작점(pos_y) + (이동한 거리(perp_wall_dist) * Y축 방향(ray_dir_y))
				wall_x = game->player.pos_y + ray.perp_wall_dist * ray.ray_dir_y;
			// ray.side == 1은 광선이 Y축 모눈종이 선(남쪽 또는 북쪽을 바라보는 벽)에 맞았음을 의미합니다.
			else
				// 반대로 Y축 벽에 맞았으므로, 벽 표면의 위치를 알기 위해 정확한 'X좌표' 도착점을 구합니다.
				wall_x = game->player.pos_x + ray.perp_wall_dist * ray.ray_dir_x;
			// 여기까지 오면 wall_x에는 5.37, 12.81 같은 실수 형태의 절대 좌표가 들어있습니다.
			// 우리는 "몇 번째 벽돌이냐(5번, 12번)"가 궁금한 게 아니라 "벽돌 표면의 몇 % 지점이냐(0.37, 0.81)"가 궁금합니다.
			// 따라서 자신의 내림값(floor)을 빼주어 정수 부분을 날려버리고 순수한 소수점(0.0 ~ 0.999...)만 남깁니다.
			wall_x -= floor(wall_x);

			/* 🚨 부동소수점 오차로 인한 텍스처 찢어짐(틈새) 방지 안전장치 */
			// 이거 필요없는거 같은데...?
			if (tex_x >= TEX_WIDTH)
				tex_x = TEX_WIDTH - 1;
			if (tex_x < 0)
				tex_x = 0;

			// 2. 텍스처 x좌표 계산
			// wall_x는 앞서 계산한 0.0 ~ 0.999 사이의 벽 표면 타격 '비율'입니다.
			// (double)TEX_WIDTH: TEX_WIDTH(예: 64)라는 정수 매크로를 실수(64.0)로 강제 변환하여,
			// wall_x(실수)와의 곱셈에서 발생할 수 있는 자료형 충돌을 막고 정밀하게 계산합니다.
			// 결과값(예: 0.35 * 64.0 = 22.4)은 텍스처 이미지 상의 정확한 실수 픽셀 위치가 됩니다.
			// (int): 컴퓨터 메모리(배열)에는 '22.4번째 인덱스'라는 것이 존재할 수 없으므로,
			// 1소수점을 가차 없이 버리고 '22'라는 정확한 정수 인덱스 번호로 만들어 줍니다.
			tex_x = (int)(wall_x * (double)TEX_WIDTH);
			// 🚨 텍스처 좌우 반전(Mirroring) 교정 조건문
			// 맵의 글로벌 좌표계(커지는 방향)와 플레이어의 시선이 엇갈려 텍스처가 뒤집혀 보이는 2가지 케이스입니다.
			// 1) ray.side == 0 (동/서쪽 벽)인데 ray_dir_x < 0 (서쪽을 바라볼 때)
			// 2) ray.side == 1 (남/북쪽 벽)인데 ray_dir_y > 0 (남쪽을 바라볼 때)
			if ((ray.side == 0 && ray.ray_dir_x < 0) || (ray.side == 1 && ray.ray_dir_y > 0))
				// 텍스처가 거울처럼 뒤집혀 있다면, 우리가 가져올 픽셀 인덱스도 강제로 반대로 뒤집어줍니다.
				// 예: TEX_WIDTH가 64이고 계산된 tex_x가 0(맨 왼쪽)이라면?
				// 64 - 0 - 1 = 63 (맨 오른쪽 인덱스로 변경!)
				// 끝에 -1을 해주는 이유는 배열의 인덱스가 1~64가 아니라 0~63이기 때문입니다.
				tex_x = TEX_WIDTH - tex_x - 1;

			// 3. 세로선 그리기
			draw_wall_line(game, x, &ray, tex_idx, tex_x);
		}
		/* 만약 ray.hit == -1 이라면? 아무것도 안 그립니다.
		   즉, 이전에 draw_background에서 칠해둔 지평선(바닥/천장)이 그대로 화면에 남습니다! */
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	game->is_moved = 0;
	return (0);
}
