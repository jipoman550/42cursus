/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:56:05 by sisung            #+#    #+#             */
/*   Updated: 2025/04/15 14:10:25 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (dsize == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len >= dsize)
		return (dsize + src_len);
	i = 0;
	while (src[i] && dst_len + i < (dsize - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	char *dst = NULL;
// 	const char *src = "hello";

// 	// dsize가 0이면 dst가 NULL이어도 문제 없어야 한다.
// 	size_t result = ft_strlcat(dst, src, 0);
// 	printf("결과: %zu\n", result);  // hello의 길이인 5가 출력되어야 함

// 	return 0;
// }