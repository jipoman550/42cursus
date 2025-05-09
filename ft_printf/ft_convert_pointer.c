/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:10:29 by sisung            #+#    #+#             */
/*   Updated: 2025/05/09 17:20:06 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	convert_pointer(va_list args)
{
	void			*ptr;
	unsigned long	address;
	int				count;

	ptr = va_arg(args, void *);
	address = (unsigned long)ptr;
	count = 0;
	if (!address)
	{
		ft_putstr_fd("(nil)", 1);
		count = 5;
	}
	else
	{
		ft_putstr_fd("0x", 1);
		count += 2;
		count += hex_len(address);
		print_hex(address, 0);
	}
	return (count);
}

// print_hex 구현해야함. -> 구현 함.
// util.c 파일을 따로 파서 몰아줘야하나?? -> 일단 x, X구현할 때 생각하기.