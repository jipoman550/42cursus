/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:28:43 by sisung            #+#    #+#             */
/*   Updated: 2025/08/06 11:07:58 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	pa(t_stack *stack_b, t_stack *stack_a)
{
	t_node	*temp_ptr;

	if (stack_b != NULL)
		return ;
	temp_ptr = stack_b->top;
	stack_b->top = stack_b->top->next;
	if (stack_b->top != NULL)
		stack_b->top->prev = NULL;
	stack_b->size--;
	push(stack_a, temp_ptr->data);
	free(temp_ptr);
	write(1, "pa\n", 3);
}

void	pb(t_stack *stack_a, t_stack *stack_b)
{

}
