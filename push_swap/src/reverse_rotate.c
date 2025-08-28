/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:07:55 by sisung            #+#    #+#             */
/*   Updated: 2025/08/06 21:33:29 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_stack *stack_a)
{
	t_node	*first_node;
	t_node	*last_node;
	t_node	*new_last_node;

	if (stack_a->size < 2)
		return ;
	first_node = stack_a->top;
	last_node = stack_a->top;
	while (last_node->next != NULL)
		last_node = last_node->next;
	new_last_node = last_node->prev;
	stack_a->top = last_node;
	last_node->prev = NULL;
	last_node->next = first_node;
	first_node->prev = last_node;
	new_last_node->next = NULL;
	write(1, "rra\n", 4);
}

void	rrb(t_stack *stack_b)
{
	t_node	*first_node;
	t_node	*last_node;
	t_node	*new_last_node;

	if (stack_b->size < 2)
		return ;
	first_node = stack_b->top;
	last_node = stack_b->top;
	while (last_node->next != NULL)
		last_node = last_node->next;
	new_last_node = last_node->prev;
	stack_b->top = last_node;
	last_node->prev = NULL;
	last_node->next = first_node;
	first_node->prev = last_node;
	new_last_node->next = NULL;
	write(1, "rrb\n", 4);
}

void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	rra(stack_a);
	rrb(stack_b);
}
