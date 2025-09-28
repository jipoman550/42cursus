/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:10:51 by sisung            #+#    #+#             */
/*   Updated: 2025/09/25 15:28:18 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(void)
{
	ft_printf("Error\n");
	exit(1);
}

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

int	main(int argc, char *argv[])
{
	char	**map;
	char	*file_name;

	if (argc != 2)
		ft_error();
	file_name = argv[1];
	if (ft_strlen(file_name) < 4
		|| ft_strncmp(file_name + ft_strlen(file_name) - 4, ".ber", 4) != 0)
		ft_error();
	map = parse_map(argv[1]);
	if (!map)
	{
		free_map(map);
		ft_error();
	}
	if (!map_validation(map))
	{
		free_map(map);
		ft_error();
	}
	free_map(map);
	return (0);
}
