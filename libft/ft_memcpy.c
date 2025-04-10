/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:14:36 by sisung            #+#    #+#             */
/*   Updated: 2025/04/08 19:04:52 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
	{
		return (NULL);
	}
	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	// char src[] = "Hello, World!";
//     // char *dest1; // 충분한 크기의 배열을 할당
//     // char *dest2;

//     // size_t n = 5;

//     // // 표준 memcpy 테스트
//     // memcpy(dest1, src, n);
//     // dest1[n] = '\0'; // 문자열 끝을 명확히 하기 위해 추가
//     // printf("memcpy:    %s\n", dest1); // 예상: "Hello"

//     // // 사용자 정의 ft_memcpy 테스트
//     // ft_memcpy(dest2, src, n);
//     // dest2[n] = '\0';
//     // printf("ft_memcpy: %s\n", dest2); // 예상: "Hello"

//	char str1[] = "123456789";
//     char str2[] = "123456789";

//     printf("Before memcpy:  %s\n", str1);
//     memcpy(str1 + 2, str1, 5);  // Overlapping 발생
//     printf("After memcpy:   %s\n", str1);  // 데이터 깨질 가능성 높음

//     printf("\nBefore memmove: %s\n", str2);
//     memmove(str2 + 2, str2, 5);  // Overlapping 발생
//     printf("After memmove:  %s\n", str2);  // 데이터 안전하게 복사됨

//     return 0;
// }