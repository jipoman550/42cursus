/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 09:17:43 by sisung            #+#    #+#             */
/*   Updated: 2025/08/07 12:47:22 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	pop(t_stack *stack)
{
	t_node	*temp_ptr;
	int		pop_data;

	if (stack == NULL || stack->size == 0)
		ft_error();
	temp_ptr = stack->top;
	pop_data = temp_ptr->data;
	stack->top = stack->top->next;
	if (stack->top != NULL)
		stack->top->prev = NULL;
	free(temp_ptr);
	stack->size--;
	return (pop_data);
}
