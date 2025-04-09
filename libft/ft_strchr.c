/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:17:29 by sisung            #+#    #+#             */
/*   Updated: 2025/04/04 19:58:17 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// void test_strchr(const char *s, int c)
// {
//     char *expected = strchr(s, c);
//     char *actual = ft_strchr(s, c);

//     printf("Input: \"%s\", Search: '%c' (%d)\n", s, c, c);
//     printf("Expected: %s\n", expected ? expected : "NULL");
//     printf("Actual  : %s\n", actual ? actual : "NULL");
//     printf("Result  : %s\n\n", (expected == actual) ? "✅ Pass" : "❌ Fail");
// }

// int main(void)
// {
//     // 1. 일반적인 케이스
//     test_strchr("hello world", 'o'); // 중간에 존재하는 문자
//     test_strchr("hello world", 'w'); // 중간에 존재하는 문자
//     test_strchr("hello world", 'd'); // 마지막 문자

//     // 2. 문자열에 없는 문자
//     test_strchr("hello world", 'z'); // 존재하지 않는 문자

//     // 3. 첫 번째 문자가 일치하는 경우
//     test_strchr("hello world", 'h');

//     // 4. 널 문자 (`\0`) 찾기
//     test_strchr("hello world", '\0');

//     // 5. 빈 문자열 테스트
//     test_strchr("", 'a');  // 빈 문자열에서 존재하지 않는 문자 찾기
//     test_strchr("", '\0'); // 빈 문자열에서 `\0` 찾기

//     // 6. 같은 문자 여러 개 있는 경우 (가장 첫 번째 것을 찾아야 함)
//     test_strchr("banana", 'a');

//     // 7. 연속된 동일 문자
//     test_strchr("aaaabbbb", 'b');

//     // 8. 숫자, 특수 문자 포함된 문자열
//     test_strchr("123@#$%", '@');

//     // 9. 문자열의 첫 번째와 마지막 문자가 같은 경우
//     test_strchr("xylophonex", 'x');

//     return 0;
// }