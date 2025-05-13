/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:33:09 by sisung            #+#    #+#             */
/*   Updated: 2025/05/13 18:08:37 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	decimal_len(int num)
{
	int	digits;

	digits = 1;
	if (num < 0)
		digits++;
	while (num / 10)
	{
		digits++;
		num /= 10;
	}
	return (digits);
}

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

int	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	char	digit;

	if (fd < 0)
		return (0);
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	digit = (n % 10) + '0';
	if (write(fd, &digit, 1) == -1)
		return (-1);
	return (0);
}

int	hex_len(unsigned long num)
{
	int	digits;

	digits = 1;
	while (num / 16)
	{
		digits++;
		num /= 16;
	}
	return (digits);
}

int	print_hex(unsigned long num, int is_upper)
{
	char	*hex_base;

	if (is_upper)
		hex_base = "0123456789ABCDEF";
	else
		hex_base = "0123456789abcdef";
	if (num >= 16)
		print_hex(num / 16, is_upper);
	if (ft_putchar_fd(hex_base[num % 16], 1) == -1)
		return (-1);
	return (0);
}
