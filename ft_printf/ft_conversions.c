/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:58:08 by sisung            #+#    #+#             */
/*   Updated: 2025/05/08 14:54:22 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_conversion(char conversion, va_list args)
{
	if (conversion == 'c')
		return (convert_char(args));
	else if (conversion == 's')
		return (convert_string(args));
	else if (conversion == 'p')
		return (convert_pointer(args));
	else if (conversion == 'd' || conversion == 'i')
		return (convert_decimal(args));
	else if (conversion == 'u')
		return (convert_unsigned(args));
	//else if (conversion == 'x')
	//	return (convert_hex_lower(args));
	//else if (conversion == 'X')
	//	return (convert_hex_upper(args));
	//else if (conversion == '%')
	//	return (convert_percent());
	return (0);
}
