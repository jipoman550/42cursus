/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:37:54 by sisung            #+#    #+#             */
/*   Updated: 2025/07/28 22:14:32 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
		return (0);

	int		token_count;
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

	// test code
	for (int i = 0; i < token_count; i++)
		printf("%d ", arr[i]);
	printf("\n");

	free_all(tokens, arr);

	return (0);
}
