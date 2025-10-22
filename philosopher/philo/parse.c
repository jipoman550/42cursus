/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:58:57 by sisung            #+#    #+#             */
/*   Updated: 2025/10/22 07:53:41 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool is_valid_digit(char *str)
{
	size_t	i;

	if (!str || *str == '\0')
		return (false);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static long long	ft_atol_safe(const char *str, bool *is_overflow)
{
	long long	result;

	result = 0;
	*is_overflow = false;
	while (*str)
	{
		if (result > LLONG_MAX / 10
			|| (result == LLONG_MAX / 10 && *str - '0' > LLONG_MAX % 10))
		{
			*is_overflow = true;
			return (LLONG_MAX);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

long long ft_parse_long(char *str)
{
	long long	num;
	bool		is_overflow;

	if (!is_valid_digit(str))
	{
		printf("Error: Argument contains non-digit characters.\n");
		return (-1);
	}
	num = ft_atoll_safe(str, &is_overflow);
	if (is_overflow)
	{
		printf("Error: Argument value exceeds maximum limit.\n");
		return (-1);
	}
	if (num <= 0)
	{
		if (*str == '0')
			 printf("Error: Argument cannot be zero.\n");
		else
			 printf("Error: Argument must be a positive integer.\n");
		return (-1);
	}
	return (num);
}
