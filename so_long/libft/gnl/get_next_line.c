/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:45:26 by sisung            #+#    #+#             */
/*   Updated: 2025/09/13 16:05:15 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_and_rest_buf(char **buffer)
{
	char	*newline_char;
	char	*extract_line;
	char	*next_buf;
	int		len;

	newline_char = gnl_strchr(*buffer, '\n');
	if (newline_char)
	{
		len = newline_char - *buffer + 1;
		extract_line = gnl_strndup(*buffer, len);
		next_buf = gnl_strndup(*buffer + len, gnl_strlen(*buffer + len));
		free(*buffer);
		*buffer = next_buf;
	}
	else
	{
		extract_line = gnl_strndup(*buffer, gnl_strlen(*buffer));
		free(*buffer);
		*buffer = NULL;
	}
	return (extract_line);
}

static char	*read_and_strjoin(int fd, char **buffer)
{
	char		*read_buf;
	int			read_value;
	char		*tmp;

	read_buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!read_buf)
		return (NULL);
	read_value = 1;
	while (read_value > 0)
	{
		read_value = read(fd, read_buf, BUFFER_SIZE);
		if (read_value == 0)
			break ;
		if (read_value == -1)
			return (free(read_buf), free(*buffer), *buffer = NULL, NULL);
		read_buf[read_value] = '\0';
		tmp = gnl_strjoin(*buffer, read_buf);
		free(*buffer);
		*buffer = tmp;
		if (gnl_strchr(read_buf, '\n'))
			break ;
	}
	return (free(read_buf), *buffer);
}

char	*get_next_line(int fd)
{
	static char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = read_and_strjoin(fd, &buf);
	if (!buf || buf[0] == '\0')
	{
		free(buf);
		buf = NULL;
		return (buf);
	}
	return (extract_and_rest_buf(&buf));
}
