/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_decimal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:35:07 by sisung            #+#    #+#             */
/*   Updated: 2025/06/03 09:46:33 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	convert_decimal(va_list args)
{
	int	decimal;
	int	count;

	decimal = va_arg(args, int);
	if (ftp_putnbr_fd(decimal, 1) == -1)
		return (-1);
	count = 0;
	count += decimal_len(decimal);
	return (count);
}
