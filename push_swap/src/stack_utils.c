/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:13:37 by sisung            #+#    #+#             */
/*   Updated: 2025/08/28 20:00:20 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
