/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_indexing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:16:26 by sisung            #+#    #+#             */
/*   Updated: 2025/08/07 21:00:52 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	create_indexed_stack(t_stack *stack_a, int *input_arr, int size)
{
	int	*sorted_arr;
	int	i;
	int	j;

	sorted_arr = (int *)malloc(sizeof(int) * size);
	if (!sorted_arr)
		fr_error();
	i = 0;
	while (i < size)
	{
		sorted_arr[i] = input_arr[i];
		i++;
	}
	selection_sort(sorted_arr, size);
	i = size - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < size)
		{
			if (input_arr[i] == sorted_arr[j])
			{
				push(stack_a, j);
				break ;
			}
			j++;
		}
		i--;
	}
	free(sorted_arr);
}
