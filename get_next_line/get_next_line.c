/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:45:26 by sisung            #+#    #+#             */
/*   Updated: 2025/05/28 14:05:46 by sisung           ###   ########.fr       */
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
	while (read_value > 0 && !ft_strchr(read_buf, '\n'))
	{
		read_value = read(fd, read_buf, BUFFER_SIZE);
		if (read_value == -1)
		{
			free(read_buf);
			return (NULL);
		}
		read_buf[read_value] = '\0';
		tmp = ft_strjoin(buf, read_buf);
		free(buf);
		buf = tmp;
	}
	char *newline_char = ft_strchr(buf, '\n');
	int newline_after_len = ft_strlen(newline_char);
	tmp = ft_strndup(newline_char, newline_after_len);
	int len = 0;
	while (buf[len] != '\n')
		len++;
	char *extract_line = ft_strndup(buf, len);
	free(buf);
	buf = tmp;
	free(read_buf);
	return (extract_line);
}
