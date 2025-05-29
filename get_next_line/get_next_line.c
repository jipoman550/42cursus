/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:45:26 by sisung            #+#    #+#             */
/*   Updated: 2025/05/29 14:07:58 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*read_buf;
	int			read_value;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

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
		{
			free(read_buf);
			return (NULL);
		}
		read_buf[read_value] = '\0';
		tmp = ft_strjoin(buf, read_buf);
		free(buf);
		buf = tmp;
		if (ft_strchr(read_buf, '\n'))
			break ;
	}
	free(read_buf);

	if (!buf || buf[0] == '\0')
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}

	char	*newline_char = ft_strchr(buf, '\n');
	char	*extract_line;
	char	*next_buf;

	if (newline_char)
	{
		int len = newline_char - buf + 1;
		extract_line = ft_strndup(buf, len);
		next_buf = ft_strndup(buf + len, ft_strlen(buf +len));
		free(buf);
		buf = next_buf;
	}
	else
	{
		extract_line = ft_strndup(buf, ft_strlen(buf));
		free(buf);
		buf = NULL;
	}
	return (extract_line);
}
