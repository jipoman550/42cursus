/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:11:04 by sisung            #+#    #+#             */
/*   Updated: 2025/09/11 16:46:03 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**parse_map(char *file_path)
{
	int		fd;
	char	**map;
	char	*line;
	char	*temp_map_str;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\n");
		exit(1);
	}
	temp_map_str = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL)
	{
		char *old_temp = temp_map_str;
		temp_map_str = ft_strjoin(temp_map_str, line);
		free(old_temp);
		line = get_next_line(fd);
	}
	close(fd);
	if (ft_strlen(temp_map_str) == 0)
	{
		ft_printf("Error\n");
		free(temp_map_str);
		exit(1);
	}
	map = ft_split(temp_map_str, '\n');
	free(temp_map_str);
	return (map);
}
