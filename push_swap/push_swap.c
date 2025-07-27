/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:37:54 by sisung            #+#    #+#             */
/*   Updated: 2025/07/13 17:38:55 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
		return (0);

	int argc_num = argc;
	int	intput_word_count = 0;
	int i = 0;
	while(i < argc_num - 1)
	{
		intput_word_count += count_words(argv[argc_num], ' ');
		i++;
	}
	char *split_arr = (char *)malloc(sizeof(char) * (intput_word_count + 1));
	if (!split_arr)
		ft_error();

	i = 1;
	int k = 0;
	while (i <= argc_num)
	{
		char **s = ft_split(argv[i], ' ');
		int j = 0;
		while (s[j] != '\0')
		{
			split_arr[k] = *s[j];
			k++;
			j++;
		}
	}
	split_arr[k] = NULL;

	int	*arr = (int *)malloc(sizeof(int) * argc);
	if (!arr)
		ft_error();

	if (!is_validate_input(argc, split_arr, arr))
	{
		free(arr);
		ft_error();
	}

	for (int i = 0; i < argc - 1; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return (0);
}
