/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:12:09 by sisung            #+#    #+#             */
/*   Updated: 2025/04/15 15:25:07 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	dup = (char *)malloc(ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "libft.h"

// int	main(void)
// {
// 	char *original = "Hi, Bye";
// 	char *dup1 = ft_strdup(original);
// 	char *dup2 = strdup(original);

// 	if (dup1 && dup2)
// 	{
// 		printf("Original  : %s\n", original);
// 		printf("ft_strdup : %s\n", dup1);
// 		printf("strdup    : %s\n", dup2);
// 	}

// 	// 메모리 해제
// 	free(dup1);
// 	free(dup2);

// 	// NULL 입력 테스트
// 	char *null_dup = ft_strdup(NULL);
// 	if (!null_dup)
// 		printf("NULL input test passed\n");

// 	return (0);
// }