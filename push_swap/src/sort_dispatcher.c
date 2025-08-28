/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:40:11 by sisung            #+#    #+#             */
/*   Updated: 2025/08/27 16:41:56 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static bool is_sorted(t_stack *stack)
{
    t_node *current;

    if (get_stack_size(stack) <= 1)
        return (true);
    current = stack->top;
    while (current && current->next)
    {
        if (current->index > current->next->index)
            return (false);
        current = current->next;
    }
    return (true);
}

void	run_sort(t_stack* stack_a, t_stack* stack_b)
{
	if (is_sorted(stack_a))
		return ;
	else if (stack_a->size <= 5)
		sort_small(stack_a, stack_b);
	else
		radix_sort(stack_a, stack_b);
}