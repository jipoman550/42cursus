/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:37:54 by sisung            #+#    #+#             */
/*   Updated: 2025/08/27 16:41:01 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char *argv[])
{
	size_t	token_count;
	char	**tokens;
	int		*arr;
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
		return (0);
	token_count = 0;
	tokens = collect_tokens(argc, argv, &token_count);
	arr = malloc(sizeof(int) * token_count);
	if (!arr)
		ft_error();
	if (!is_validate_input(token_count, tokens, arr))
	{
		free_all(tokens, arr);
		ft_error();
	}
	stack_a = create_stack();
	create_indexed_stack(stack_a, arr, token_count);
	stack_b = create_stack();
	run_sort(stack_a, stack_b);
	free_stack_a_and_stack_b(stack_a, stack_b);
	free_all(tokens, arr);
	return (0);
}
