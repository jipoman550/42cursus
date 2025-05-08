/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:46:13 by sisung            #+#    #+#             */
/*   Updated: 2025/05/08 17:47:29 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	unsigned_len(unsigned int num)
{
	int	digits;

	digits = 1;
	while (num / 10)
	{
		digits++;
		num /= 10;
	}
	return (digits);
}

void	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	char	digit;

	if (fd < 0)
		return ;
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	digit = (n % 10) + '0';
	write(fd, &digit, 1);
}

int	convert_unsigned(va_list args)
{
	unsigned int	uint_arg;
	int				count;

	uint_arg = va_arg(args, unsigned int);
	ft_putnbr_unsigned_fd(uint_arg, 1);
	count = 0;
	count += unsigned_len(uint_arg);
	return (count);
}
