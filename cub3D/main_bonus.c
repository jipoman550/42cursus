/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 23:25:18 by sisung            #+#    #+#             */
/*   Updated: 2026/02/19 23:25:19 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D <map_file.cub>\n");
		return (1);
	}
	(void)argv;
	printf("cub3D Bonus started\n");
	return (0);
}