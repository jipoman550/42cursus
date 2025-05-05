/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:25:25 by sisung            #+#    #+#             */
/*   Updated: 2025/05/05 18:02:19 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	convert_string(va_list args)
{
	char *s;
	int len;

	s = va_arg(args, char *);
	len = ft_strlen(s);
	ft_putstr_fd(s, 1);
	return (len);
}

// !s 일 때도 처리를 해줘야하나?