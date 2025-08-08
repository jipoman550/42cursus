/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_indexing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:16:26 by sisung            #+#    #+#             */
/*   Updated: 2025/08/08 18:59:39 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	selection_sort(int *arr, int size)
{
	int	i;
	int	j;
	int	min_idx;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		min_idx = i;
		j = i + 1;
		while (j < size)
		{
			if (arr[j] < arr[min_idx])
				min_idx = j;
			j++;
		}
		if (min_idx != i)
		{
			temp = arr[i];
			arr[i] = arr[min_idx];
			arr[min_idx] = temp;
		}
		i++;
	}
}

static void	stack_in_index(t_stack *stk_a, int *i_a, int *s_a, int s)
{
	int	i;
	int	j;

	i = s - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < s)
		{
			if (i_a[i] == s_a[j])
			{
				push(stk_a, j);
				break ;
			}
			j++;
		}
		i--;
	}
}

void	create_indexed_stack(t_stack *stack_a, int *input_arr, int size)
{
	int	*sorted_arr;
	int	i;

	sorted_arr = (int *)malloc(sizeof(int) * size);
	if (!sorted_arr)
		ft_error();
	i = 0;
	while (i < size)
	{
		sorted_arr[i] = input_arr[i];
		i++;
	}
	selection_sort(sorted_arr, size);
	stack_in_index(stack_a, input_arr, sorted_arr, size);
	free(sorted_arr);
}
