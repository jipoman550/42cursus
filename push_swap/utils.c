/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:18:48 by sisung            #+#    #+#             */
/*   Updated: 2025/07/28 22:19:12 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

size_t	ft_strlen(const char *s)
{
	if (!s)
		return (0);

	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		cnt++;
		s++;
	}
	return (cnt);
}

void	free_str_array(char **arr)
{
	if (!arr)
		ft_error();

	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_int_array(int *arr)
{
	if (!arr)
		ft_error();
	free(arr);
}

void	free_all(char **strs, int *nums)
{
	free_str_array(strs);
	free_int_array(nums);
}

void	ft_error()
{
	write(2, "Error\n", 6);
	exit(1);
}