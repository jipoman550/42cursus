/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:46:13 by sisung            #+#    #+#             */
/*   Updated: 2025/08/06 21:34:05 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack *stack_a)
{
	t_node	*first_node;
	t_node	*second_node;
	t_node	*third_node;

	if (stack_a->size < 2)
		return ;
	first_node = stack_a->top;
	second_node = first_node->next;
	third_node = second_node->next;
	stack_a->top = second_node;
	second_node->prev = NULL;
	second_node->next = first_node;
	first_node->prev = second_node;
	first_node->next = third_node;

	if (third_node != NULL)
		third_node->prev = first_node;
	write(1, "sa\n", 3);
}

void	sb(t_stack *stack_b)
{
	t_node	*first_node;
	t_node	*second_node;
	t_node	*third_node;

	if (stack_b->size < 2)
		return ;
	first_node = stack_b->top;
	second_node = first_node->next;
	third_node = second_node->next;
	stack_b->top = second_node;
	second_node->prev = NULL;
	second_node->next = first_node;
	first_node->prev = second_node;
	first_node->next = third_node;
	if (third_node != NULL)
		third_node->prev = first_node;
	write(1, "sb\n", 3);
}

void	ss(t_stack *stack_a, t_stack *stack_b)
{
	sa(stack_a);
	sb(stack_b);
}
