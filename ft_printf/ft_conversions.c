/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:58:08 by sisung            #+#    #+#             */
/*   Updated: 2025/05/01 18:33:03 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_conversion(char conversion, va_list args)
{
	if (conversion == 'c')
		return convert_char(args);
	else if (conversion == 's')
		return convert_string(args);
	else if (conversion == 'p')
		return convert_pointer(args);
	else if (conversion == 'd')
		return convert_decimal(args);
	else if (conversion == 'i')
		return convert_integer(args);
	else if (conversion == 'u')
		return convert_unsigned_decimal(args);
	else if (conversion == 'x')
		return convert_hexadecimal_lowercase(args);
	else if (conversion == 'X')
		return convert_hexadecimal_uppercase(args);
	else if (conversion == '%')
		return convert_percent();
	return (0);
}
