/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:45:26 by sisung            #+#    #+#             */
/*   Updated: 2025/05/23 17:03:25 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*read_buf;
	int			read_value;
	char		*tmp;

	read_buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!read_buf)
		return (NULL);
	read_value = read(fd, read_buf, BUFFER_SIZE);
	if (read_value < 0)
	{
		free(read_buf);
		return (NULL);
	}
	tmp = ft_strjoin(buf, read_buf);
	free(buf);
	buf = tmp;
	return (read_buf);
}
