/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:52:20 by sisung            #+#    #+#             */
/*   Updated: 2025/04/23 15:28:17 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		count++;
	}
	return (count);
}

static void	fill_str(char *str, long num, int digit_cnt, int sign)
{
	int	i;

	i = sign + digit_cnt - 1;
	if (num == 0)
		str[i--] = '0';
	while (num)
	{
		str[i--] = (num % 10) + '0';
		num /= 10;
	}
	if (sign)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	int		digit_cnt;
	int		sign;
	char	*str;
	long	num;

	num = n;
	sign = 0;
	if (num < 0)
	{
		sign = 1;
		num = -num;
	}
	digit_cnt = count_digits(num);
	str = (char *)malloc(sizeof(char) * (sign + digit_cnt + 1));
	if (!str)
		return (NULL);
	str[sign + digit_cnt] = '\0';
	fill_str(str, num, digit_cnt, sign);
	return (str);
}
