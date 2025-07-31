/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:37:54 by sisung            #+#    #+#             */
/*   Updated: 2025/07/31 21:21:09 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
		return (0);

	size_t	token_count;
	char	**tokens;
	int		*arr;

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
