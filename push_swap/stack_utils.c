/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:13:37 by sisung            #+#    #+#             */
/*   Updated: 2025/08/04 21:19:13 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

int	peek(t_stack *stack)
{
	if (stack->top == NULL)
		ft_error();
	return (stack->top->data);
}

bool	is_empty(t_stack *stack)
{
	if (stack->top == NULL)
		return (1);
	return (0);
}

size_t	get_stack_size(t_stack *stack)
{
	return (stack->size);
}
