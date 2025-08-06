/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 09:17:43 by sisung            #+#    #+#             */
/*   Updated: 2025/08/06 10:37:23 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

void	push(t_stack *stack, int data)
{
	t_node	*new_node_ptr;

	new_node_ptr = new_node(data);
	if (!new_node_ptr)
		ft_error();
	if (stack->top == NULL)
	{
		stack->top = new_node_ptr;
	}
	else
	{
		new_node_ptr->next = stack->top;
		stack->top->prev = new_node_ptr;
		stack->top = new_node_ptr;
	}
	stack->size++;
}

void	pop(t_stack *stack)
{
	t_node	*temp_ptr;

	if (stack->top == NULL)
		return ;
	temp_ptr = stack->top;
	stack->top = stack->top->next;
	if (stack->top != NULL)
		stack->top->prev = NULL;
	free(temp_ptr);
	stack->size--;
}
