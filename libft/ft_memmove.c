/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:39:36 by sisung            #+#    #+#             */
/*   Updated: 2025/04/21 17:35:37 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
	{
		return (NULL);
	}
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (s < d && d < s + n)
	{
		while (n--)
		{
			d[n] = s[n];
		}
	}
	else
	{
		while (n--)
		{
			*d++ = *s++;
		}
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     char str1[] = "Hello, World!";
//     char str2[] = "Hello, World!";

//     printf("Before ft_memmove (Overlap Test 1): %s\n", str1);
//     ft_memmove(str1 + 6, str1, 6);  // 같은 배열 내에서 앞에서 뒤로 복사
//     printf("After ft_memmove (Overlap Test 1) : %s\n", str1);

//     printf("\nBefore memmove (Overlap Test 2): %s\n", str2);
//     memmove(str2 + 6, str2, 6);  // C 표준 라이브러리 memmove()로 테스트
//     printf("After memmove (Overlap Test 2) : %s\n", str2);

//     return 0;
// }