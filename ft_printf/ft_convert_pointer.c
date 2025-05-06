/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:10:29 by sisung            #+#    #+#             */
/*   Updated: 2025/05/06 18:24:45 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	convert_pointer(va_list args)
{
	void	*ptr;
	unsigned long	address;
	int		count;

	ptr = (unsigned long)va_arg(args, void *);
	address = (unsigned long)ptr;
	count = 0;
	if (address == 0)
	{
		ft_putchar_fd("0", 1);
		count = 1;
	}
	else if (!address)
	{
		ft_putchar_fd("(nil)", 1);
		count = 5;
	}
	else
	{
		ft_putstr_fd("0x", 1);
		count += 2;
		count += print_hex(address);
	}
	return (count);
}

// print_hex 구현해야함.
// util.c 파일을 따로 파서 몰아줘야하나??