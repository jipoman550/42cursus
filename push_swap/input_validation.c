/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:01:46 by sisung            #+#    #+#             */
/*   Updated: 2025/07/13 17:45:09 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

static int	is_all_whitespace_or_is_len_zero(const char *s)
{
	int	i;

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

static int	is_numberic(const char *s)
{
	int	i;

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
		if (s[i] < '0' && s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_atoi_long(const char *nptr)
{
	int			i;
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

static int	is_duplicate(long long n, int *arr, int current_count)
{
	int	i;

	i = 1;
	while (i < current_count)
	{
		if (arr[i] == n)
			return (1);
		i++;
	}
	return (0);
}

bool is_validate_input(int ac, char **av, int *arr)
{
	int 		i;
	long long num;

	i = 1;
	while (i < ac)
	{
		if (is_all_whitespace_or_is_len_zero(av[i]))
			return (0);
		if (!is_numberic(av[i]))
			return (0);
		num = ft_atoi_long(av[i]);
		if (num < INT_MIN || num > INT_MAX)
			return (0);
		if (is_duplicate(num, arr, i - 1))
			return (0);
		arr[i - 1] = (int)num;
		i++;
	}
	return (1);
}
