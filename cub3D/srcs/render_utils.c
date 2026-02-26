/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:43:09 by sisung            #+#    #+#             */
/*   Updated: 2026/02/26 10:43:10 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief 이미지 버퍼의 (x, y) 좌표에 색상을 기록
 * @param img 픽셀을 그릴 대상 이미지 구조체
 * @param x 픽셀의 x 좌표
 * @param y 픽셀의 y 좌표
 * @param color 기록할 색상 값 (TRGB)
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
 * @brief 화면 전체를 천장과 바닥 색상으로 미리 채움
 * @param game 게임 구조체 포인터
 */
void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			if (y < SCREEN_H / 2)
				put_pixel(&game->img, x, y, game->map.ceil_color);
			else
				put_pixel(&game->img, x, y, game->map.floor_color);
			x++;
		}
		y++;
	}
}
