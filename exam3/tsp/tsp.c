/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jaeholee <makest@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:30:43 by Jaeholee          #+#    #+#             */
/*   Updated: 2025/08/05 15:30:43 by Jaeholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define MAX_N 11

enum e_postion
{
	x,
	y
};

int printxy(float p_xy[MAX_N][2], int count)
{
	int i = -1;
	while (++i < count)
		printf("p_xy[%d][0]: %.2f p_xy[%d][1] %.2f\n", i, p_xy[i][x], i, p_xy[i][y]);
	return (0);
}

int cal_distance(float p_xy[MAX_N][2], float *tmp_len, int now, int pre)
{
	
	float dx = 0;
	float dy = 0;
	dx = p_xy[pre][x] - p_xy[now][x];
	dy = p_xy[pre][y] - p_xy[now][y];
	*tmp_len = sqrtf((dx * dx) + (dy * dy));
	return (0);
}

int tsp_dfs(float p_xy[MAX_N][2], float pathlen, float *final_path, size_t visited, int count, int pre)
{
	float tmp_len = 0;
	if (visited == (1UL << count) - 1)
	{
		cal_distance(p_xy, &tmp_len, 0, pre);
		pathlen += tmp_len;
		if (pathlen < *final_path)
			*final_path = pathlen;
		return (0);
	}
	int i = 0;
	while (++i < count)
	{
		if (!(visited & (1UL << i)))
		{
			cal_distance(p_xy, &tmp_len, i, pre);
			pathlen += tmp_len;
			if (pathlen < *final_path)
				tsp_dfs(p_xy, pathlen, final_path, visited | (1UL << i), count, i);
			pathlen -= tmp_len;
		}
	}
	return (0);
}

int main(void)
{
	FILE *in = fopen("/home/jaeholee/SUBJECT/git_forder/exam3/tsp/cities.txt", "r");
	int count = 0;
	float p_xy[MAX_N][2] = {0};
	while (count < MAX_N && fscanf(in, "%f, %f\n", &p_xy[count][x], &p_xy[count][y]) == 2)
		count++;
	// 만약 점이 1개
	if (count < 2)
	{
		fprintf(stdout, "final_path: %.2f\n", 0);
		return (0);
	}
	printxy(p_xy, count);
	float pathlen = 0;
	float final_path = FLT_MAX;
	tsp_dfs(p_xy, pathlen, &final_path, 1, count, 0);
	printf("==answer==");
	fprintf(stdout, "final_path: %.2f\n", final_path);
	fclose(in);
	return (0);
}
