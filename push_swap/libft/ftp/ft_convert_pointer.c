/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:10:29 by sisung            #+#    #+#             */
/*   Updated: 2025/06/03 09:46:13 by sisung           ###   ########.fr       */
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
		if (ftp_putstr_fd("(nil)", 1) == -1)
			return (-1);
		count = 5;
	}
	else
	{
		if (ftp_putstr_fd("0x", 1) == -1)
			return (-1);
		count += 2;
		if (print_hex(address, 0) == -1)
			return (-1);
		count += hex_len(address);
	}
	return (count);
}
