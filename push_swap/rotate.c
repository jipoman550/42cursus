/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:55:06 by sisung            #+#    #+#             */
/*   Updated: 2025/08/06 21:33:36 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_stack *stack_a)
{
	t_node	*first_node;
	t_node	*last_node;

	if (stack_a->size < 2)
		return ;
	first_node = stack_a->top;
	last_node = stack_a->top;
	while (last_node->next != NULL)
		last_node = last_node->next;
	stack_a->top = first_node->next;
	stack_a->top->prev = NULL;
	last_node->next = first_node;
	first_node->prev = last_node;
	first_node->next = NULL;
	write(1, "ra\n", 3);
}

void	rb(t_stack *stack_b)
{
	t_node	*first_node;
	t_node	*last_node;

	if (stack_b->size < 2)
		return ;
	first_node = stack_b->top;
	last_node = stack_b->top;
	while (last_node->next != NULL)
		last_node = last_node->next;
	stack_b->top = first_node->next;
	stack_b->top->prev = NULL;
	last_node->next = first_node;
	first_node->prev = last_node;
	first_node->next = NULL;
	write(1, "rb\n", 3);
}

void	rr(t_stack *stack_a, t_stack *stack_b)
{
	ra(stack_a);
	rb(stack_b);
}
