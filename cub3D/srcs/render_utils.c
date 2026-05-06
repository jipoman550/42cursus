/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:43:09 by sisung            #+#    #+#             */
/*   Updated: 2026/05/06 18:23:56 by sisung           ###   ########.fr       */
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

	// 메모리의 특정 주소에 색상 값을 기록하는 역할
	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief 화면 전체를 천장과 바닥 색상으로 미리 채움 (최적화 버전)
 * @details 2차원 연산과 put_pixel 호출을 제거하고, 1차원 int 배열로 메모리를 직접 밀어버립니다.
 * @param game 게임 구조체 포인터
 */
void	draw_background(t_game *game)
{
	unsigned int	*dst;
	int				i;
	int				total_pixels;
	int				half_pixels;

	/* 1바이트 단위인 addr을 4바이트(픽셀) 단위 포인터로 캐스팅 */
	dst = (unsigned int *)game->img.addr;

	/* 전체 픽셀 개수 = (세로 픽셀 수 * 가로 한 줄의 바이트 수) / 4바이트 */
	total_pixels = (SCREEN_H * game->img.line_len) / 4;
	half_pixels = total_pixels / 2;
	i = 0;
	while (i < total_pixels)
	{
		if (i < half_pixels)
		{
			dst[i] = game->map.ceil_color;
		}
		else
		{
			dst[i] = game->map.floor_color;
		}
		i++;
	}
}
