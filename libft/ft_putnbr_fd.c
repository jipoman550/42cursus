/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:30:05 by sisung            #+#    #+#             */
/*   Updated: 2025/04/14 18:47:56 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	digit;

	if (fd < 0)
		return ;
	num = (long)n;
	if (num < 0)
	{
		num = -num;
		write(fd, &"-", 1);
	}
	if (num >= 10)
		ft_putnbr_fd(num / 10, fd);
	digit = (num % 10) + '0';
	write(fd, &digit, 1);
}

// int main()
// {
// 	int n = 0;
// 	ft_putnbr_fd(n, 1);
// 	return 0;
// }