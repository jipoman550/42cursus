/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:23:01 by sisung            #+#    #+#             */
/*   Updated: 2025/05/13 18:25:15 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printed_chars(const char *format, va_list args)
{
	int	printed_chars;
	int	result;

	printed_chars = 0;
	result = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			result = handle_conversion(*format, args);
			if (result == -1)
				return (-1);
			printed_chars += result;
			format++;
		}
		else
		{
			if (write(1, format, 1) == -1)
			{
				va_end(args);
				return (-1);
			}
			printed_chars++;
			format++;
		}
	}
	return (printed_chars);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed_chars;
	int		result;

	if (!format)
		return (-1);
	printed_chars = 0;
	result = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			result = handle_conversion(*format, args);
			if (result == -1)
				return (-1);
			printed_chars += result;
			format++;
		}
		else
		{
			if (write(1, format, 1) == -1)
			{
				va_end(args);
				return (-1);
			}
			printed_chars++;
			format++;
		}
	}
	va_end(args);
	return (printed_chars);
}
