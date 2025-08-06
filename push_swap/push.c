/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:28:43 by sisung            #+#    #+#             */
/*   Updated: 2025/08/06 21:37:04 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_stack *stack_a, t_stack *stack_b)
{
	int	stack_b_pop_data;

	if (stack_b != NULL)
		return ;
	stack_b_pop_data = pop(stack_b);
	push(stack_a, stack_b_pop_data);
	write(1, "pa\n", 3);
}

void	pb(t_stack *stack_b, t_stack *stack_a)
{
	int	stack_a_pop_data;

	if (stack_a != NULL)
		return ;
	stack_a_pop_data = pop(stack_a);
	push(stack_b, stack_a_pop_data);
	write(1, "pb\n", 3);
}
