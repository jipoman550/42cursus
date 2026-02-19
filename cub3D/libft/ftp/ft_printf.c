/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:23:01 by sisung            #+#    #+#             */
/*   Updated: 2025/05/15 14:58:54 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printed_chars(const char *format, va_list args)
{
	int	count;
	int	temp;

	count = 0;
	temp = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			temp = handle_conversion(*format, args);
			if (temp == -1)
				return (-1);
			count += temp;
			format++;
		}
		else
		{
			if (write(1, format, 1) == -1)
				return (-1);
			count++;
			format++;
		}
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	count = 0;
	va_start(args, format);
	count = ft_printed_chars(format, args);
	va_end(args);
	return (count);
}
