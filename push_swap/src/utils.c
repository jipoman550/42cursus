/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:18:48 by sisung            #+#    #+#             */
/*   Updated: 2025/08/19 13:58:23 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_str_array(char **arr)
{
	size_t	i;

	if (!arr)
		ft_error();
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_int_array(int *arr)
{
	if (!arr)
		ft_error();
	free(arr);
}

void	free_all(char **strs, int *nums)
{
	free_str_array(strs);
	free_int_array(nums);
}

void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	get_min_index_pos(t_stack *stack)
{
	t_node	*current;
	size_t	min_index;
	int		pos;
	int		min_pos;

	current = stack->top;
	min_index = current->index;
	pos = 0;
	min_pos = 0;
	while (current)
	{
		if (current->index < min_index)
		{
			min_index = current->index;
			min_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (min_pos);
}
