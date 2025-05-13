/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:30:05 by sisung            #+#    #+#             */
/*   Updated: 2025/05/13 18:07:05 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	digit;

	if (fd < 0)
		return (0);
	num = (long)n;
	if (num < 0)
	{
		num = -num;
		if (write(fd, &"-", 1) == -1)
			return (-1);
	}
	if (num >= 10)
		ft_putnbr_fd(num / 10, fd);
	digit = (num % 10) + '0';
	if (write(fd, &digit, 1) == -1)
		return (-1);
	return (0);
}
