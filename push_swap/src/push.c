/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:28:43 by sisung            #+#    #+#             */
/*   Updated: 2025/08/07 13:06:23 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*node_to_push;

	if (stack_b == NULL || stack_b->size == 0)
		return ;
	node_to_push = pop(stack_b);
	push(stack_a, node_to_push->data, node_to_push->index);
	free(node_to_push);
	write(1, "pa\n", 3);
}

void	pb(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*node_to_push;

	if (stack_a == NULL || stack_a->size == 0)
		return ;
	node_to_push = pop(stack_a);
	push(stack_b, node_to_push->data, node_to_push->index);
	free(node_to_push);
	write(1, "pb\n", 3);
}
