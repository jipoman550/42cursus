/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:37:54 by sisung            #+#    #+#             */
/*   Updated: 2025/08/01 18:16:36 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

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

	//// test code
	//for (size_t i = 0; i < token_count; i++)
	//	printf("%d ", arr[i]);
	//printf("\n");

	//free_all(tokens, arr);

	return (0);
}
