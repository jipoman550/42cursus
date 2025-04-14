/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:34 by sisung            #+#    #+#             */
/*   Updated: 2025/04/14 18:13:41 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s || fd < 0)
		return ;
	len = ft_strlen(s);
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

// int main()
// {
// 	char *s = "hello, world!";
// 	ft_putstr_fd(s, 1);
// 	write(1, "\n", 1);
// 	return (0);
// }