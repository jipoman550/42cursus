/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:46:13 by sisung            #+#    #+#             */
/*   Updated: 2025/05/13 17:57:12 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	convert_unsigned(va_list args)
{
	unsigned int	uint_arg;
	int				count;

	uint_arg = va_arg(args, unsigned int);
	if (ft_putnbr_unsigned_fd(uint_arg, 1) == -1)
		return (-1);
	count = 0;
	count += unsigned_len(uint_arg);
	return (count);
}
