/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:58:57 by sisung            #+#    #+#             */
/*   Updated: 2025/10/27 10:46:49 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_valid_digit(char *str)
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

long long	ft_parse_long(char *str)
{
	long long	num;
	bool		is_overflow;

	if (!is_valid_digit(str))
		return (error_and_return(NON_DIGIT_CHAR, -1));
	num = ft_atol_safe(str, &is_overflow);
	if (is_overflow)
		return (error_and_return(EXCEED_MAX_LIMIT, -1));
	if (num <= 0)
	{
		if (*str == '0')
			return (error_and_return(CANT_BE_ZERO, -1));
		else
			return (error_and_return(NOT_POSITIVE_INT, -1));
	}
	return (num);
}
