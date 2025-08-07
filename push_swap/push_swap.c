/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:37:54 by sisung            #+#    #+#             */
/*   Updated: 2025/08/07 20:40:35 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char *argv[])
{
	size_t	token_count;
	char	**tokens;
	int		*arr;

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
	// arr에 있는 값들을 정렬해서 인덱싱해야됨.
	t_stack	*stack_a = create_stack();
	create_indexed_stack(stack_a, arr, token_count);


	return (0);
}
