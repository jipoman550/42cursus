/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:36:26 by sisung            #+#    #+#             */
/*   Updated: 2025/05/09 16:55:24 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	convert_hex(char conversion, va_list args)
{
	unsigned int	hex;
	int				count;

	hex = va_arg(args, unsigned int);
	if (conversion == 'x')
		print_hex((unsigned long)hex, 0);
	else if (conversion == 'X')
		print_hex((unsigned long)hex, 1);
	count = 0;
	count += hex_len((unsigned long) hex);
	return (count);
}
