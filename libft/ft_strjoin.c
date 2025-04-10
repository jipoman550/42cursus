/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:04:19 by sisung            #+#    #+#             */
/*   Updated: 2025/04/09 16:12:40 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_safe(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	len = ft_strlen(s);
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*strjoin;
	char	*p;

	s1_len = ft_strlen_safe(s1);
	s2_len = ft_strlen_safe(s2);
	strjoin = (char *)malloc(s1_len + s2_len + 1);
	if (!strjoin)
		return (NULL);
	p = strjoin;
	while (s1 && *s1)
		*p++ = *s1++;
	while (s2 && *s2)
		*p++ = *s2++;
	*p = '\0';
	return (strjoin);
}

// #include <stdio.h>

// char	*ft_strjoin(char const *s1, char const *s2);

// int main(void)
// {
//     char *result;

//     // 테스트 1: 둘 다 빈 문자열
//     result = ft_strjoin("", "");
//     printf("Test 1 - Empty strings: \"%s\"\n", result);
//     free(result);

//     // 테스트 2: s1은 빈 문자열, s2는 일반 문자열
//     result = ft_strjoin("", "World");
//     printf("Test 2 - Empty s1: \"%s\"\n", result);
//     free(result);

//     // 테스트 3: s1은 일반 문자열, s2는 빈 문자열
//     result = ft_strjoin("Hello", "");
//     printf("Test 3 - Empty s2: \"%s\"\n", result);
//     free(result);

//     // 테스트 4: 둘 다 일반 문자열
//     result = ft_strjoin("Hello", "World");
//     printf("Test 4 - Normal strings: \"%s\"\n", result);
//     free(result);

//     // 테스트 5: s1이 NULL인 경우
//     result = ft_strjoin(NULL, "World");
//     if (result)
//     {
//         printf("Test 5 - s1 NULL: \"%s\"\n", result);
//         free(result);
//     }
//     else
//         printf("Test 5 - s1 NULL: NULL 반환\n");

//     // 테스트 6: s2가 NULL인 경우
//     result = ft_strjoin("Hello", NULL);
//     if (result)
//     {
//         printf("Test 6 - s2 NULL: \"%s\"\n", result);
//         free(result);
//     }
//     else
//         printf("Test 6 - s2 NULL: NULL 반환\n");

//     // 테스트 7: 둘 다 NULL인 경우
//     result = ft_strjoin(NULL, NULL);
//     if (result)
//     {
//         printf("Test 7 - Both NULL: \"%s\"\n", result);
//         free(result);
//     }
//     else
//         printf("Test 7 - Both NULL: NULL 반환\n");

//     return (0);
// }