/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:10:51 by sisung            #+#    #+#             */
/*   Updated: 2025/09/13 17:44:15 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		++i;
	}
}

int	main(int argc, char *argv[])
{
	char	**map;

	if (argc != 2)
	{
		ft_printf("Usage: ./test_program <map_file.ber>\n");
		return (1);
	}
	map = parse_map(argv[1]);
	if (map)
	{
		ft_printf("Map parsing sucessfull.\n");
		print_map(map);
		free_map(map);
	}
	else
	{
		ft_printf("Map parsing failed\n");
	}
	return (0);
}
