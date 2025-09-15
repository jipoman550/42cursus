/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:10:51 by sisung            #+#    #+#             */
/*   Updated: 2025/09/15 15:16:34 by sisung           ###   ########.fr       */
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
	char	*file_name;

	if (argc != 2)
		ft_error();
	file_name = argv[1];
	if (ft_strlen(file_name) < 4 || \
		ft_strncmp(file_name + ft_strlen(file_name) - 4, ".ber", 4) != 0)
		ft_error();
	map = parse_map(argv[1]);
	map_validation(map);
	if (map)
	{
		ft_printf("Map parsing sucessfull.\n");
		print_map(map);
	}
	else
	{
		ft_printf("Map parsing failed\n");
	}
	free_map(map);
	return (0);
}
