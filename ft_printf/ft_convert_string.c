/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:25:25 by sisung            #+#    #+#             */
/*   Updated: 2025/05/13 17:46:17 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	convert_string(va_list args)
{
	char	*s;
	int		len;

	s = va_arg(args, char *);
	if (s == NULL)
	{
		if (ft_putstr_fd("(null)", 1) == -1)
			return (-1);
		len = 6;
	}
	else
	{
		if (ft_putstr_fd(s, 1) == -1)
			return (-1);
		len = ft_strlen(s);
	}
	return (len);
}
