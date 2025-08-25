/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:29:59 by sisung            #+#    #+#             */
/*   Updated: 2025/08/25 21:50:52 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	find_max_bits(t_stack *stack)
{
	size_t	max_val;
	size_t	bits;

	if (stack == NULL)
		ft_error();
	max_val = stack->size - 1;
	bits = 0;
	if (max_val == 0)
		return (1);
	while (max_val > 0)
	{
		max_val >>= 1;
		bits++;
	}
	return (bits);
}

void	radix_sort(t_stack *stack_a, t_stack * stack_b)
{
	size_t	max_bits;
	size_t	i;
	size_t	j;
	size_t	stack_size;

	if (stack_a == NULL || stack_b == NULL)
		ft_error();
	max_bits = find_max_bits(stack_a);
	stack_size = stack_a->size;
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < stack_size)
		{
			if (((stack_a->top->index >> i) & 1) == 0)
				pb(stack_a, stack_b);
			else
				ra(stack_a);
			j++;
		}
		while (stack_b->size)
			pa(stack_a, stack_b);
		i++;
	}
}
