/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:01:46 by sisung            #+#    #+#             */
/*   Updated: 2025/08/31 16:02:54 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static bool	is_all_whitespace_or_is_len_zero(const char *s)
{
	size_t	i;

	if (!s || *s == '\0')
		return (1);
	i = 0;
	while (s[i])
	{
		if (!(s[i] >= 9 && s[i] <= 13) && s[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

static bool	is_numberic(const char *s)
{
	size_t	i;

	if (!s || *s == '\0')
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		i++;
		if (s[i] == '\0')
			return (0);
	}
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atoi_long(const char *nptr)
{
	size_t		i;
	int			sign;
	long long	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ret = ret * 10 + nptr[i] - '0';
		i++;
	}
	return (sign * ret);
}

static bool	is_duplicate(long long n, int *arr, size_t current_count)
{
	size_t	i;

	i = 0;
	while (i < current_count)
	{
		if (arr[i] == n)
			return (1);
		i++;
	}
	return (0);
}

bool	is_validate_input(size_t tokens_count, char **tokens, int *arr)
{
	size_t		i;
	long long	num;

	i = 0;
	if (tokens_count == 0)
		return (0);
	while (i < tokens_count)
	{
		if (is_all_whitespace_or_is_len_zero(tokens[i]))
			return (0);
		if (!is_numberic(tokens[i]))
			return (0);
		num = ft_atoi_long(tokens[i]);
		if (num < INT_MIN || num > INT_MAX)
			return (0);
		if (is_duplicate(num, arr, i))
			return (0);
		arr[i] = (int)num;
		i++;
	}
	return (1);
}
