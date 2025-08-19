/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:00:00 by gemini            #+#    #+#             */
/*   Updated: 2025/08/19 13:58:03 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_2(t_stack *stack_a);
static void	sort_3(t_stack *stack_a);
static void	sort_4(t_stack *stack_a, t_stack *stack_b);
static void	sort_5(t_stack *stack_a, t_stack *stack_b);

void	sort_small(t_stack *stack_a, t_stack *stack_b)
{
	int	size;

	size = get_stack_size(stack_a);
	if (size == 2)
		sort_2(stack_a);
	else if (size == 3)
		sort_3(stack_a);
	else if (size == 4)
		sort_4(stack_a, stack_b);
	else if (size == 5)
		sort_5(stack_a, stack_b);
}

static void	sort_2(t_stack *stack_a)
{
	if (stack_a->top->index > stack_a->top->next->index)
		sa(stack_a);
}

static void	sort_3(t_stack *stack_a)
{
	int	top;
	int	mid;
	int	bot;

	top = stack_a->top->index;
	mid = stack_a->top->next->index;
	bot = stack_a->top->next->next->index;
	if (top > mid && mid < bot && top < bot)
		sa(stack_a);
	else if (top > mid && mid > bot)
	{
		sa(stack_a);
		rra(stack_a);
	}
	else if (top > mid && mid < bot && top > bot)
		ra(stack_a);
	else if (top < mid && mid > bot && top < bot)
	{
		sa(stack_a);
		ra(stack_a);
	}
	else if (top < mid && mid > bot && top > bot)
		rra(stack_a);
}

static void	sort_4(t_stack *stack_a, t_stack *stack_b)
{
	int	min_pos;

	min_pos = get_min_index_pos(stack_a);
	if (min_pos == 1)
		ra(stack_a);
	else if (min_pos == 2)
	{
		ra(stack_a);
		ra(stack_a);
	}
	else if (min_pos == 3)
		rra(stack_a);
	pb(stack_a, stack_b);
	sort_3(stack_a);
	pa(stack_a, stack_b);
}

static void	sort_5(t_stack *stack_a, t_stack *stack_b)
{
	int	min_pos;

	min_pos = get_min_index_pos(stack_a);
	if (min_pos == 1)
		ra(stack_a);
	else if (min_pos == 2)
	{
		ra(stack_a);
		ra(stack_a);
	}
	else if (min_pos == 3)
	{
		rra(stack_a);
		rra(stack_a);
	}
	else if (min_pos == 4)
		rra(stack_a);
	pb(stack_a, stack_b);
	sort_4(stack_a, stack_b);
	pa(stack_a, stack_b);
}
