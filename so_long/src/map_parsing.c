/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:11:04 by sisung            #+#    #+#             */
/*   Updated: 2025/10/01 09:32:24 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**parse_map(char *file_path)
{
	int		fd;
	char	**map;
	char	*line;
	char	*temp_map_str;
	char	*old_temp;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	temp_map_str = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		old_temp = temp_map_str;
		temp_map_str = ft_strjoin(temp_map_str, line);
		free(old_temp);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (temp_map_str == NULL)
		return (NULL);
	map = ft_split(temp_map_str, '\n');
	free(temp_map_str);
	return (map);
}
