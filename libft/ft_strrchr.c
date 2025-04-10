/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:40:27 by sisung            #+#    #+#             */
/*   Updated: 2025/04/05 15:49:58 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>

// int main()
// {
// 	char *s = "abcdeabcde";
//     // (1) 존재하는 문자 찾기
//     printf("Test 1: %s\n", strrchr(s, 'a'));  // 기대 출력: "abcde"

//     // (2) 문자열의 마지막 문자 찾기
//     printf("Test 2: %s\n", strrchr(s, 'e'));  // 기대 출력: "e"

//     // (3) 없는 문자 찾기
//     printf("Test 3: %s\n", strrchr(s, 'z'));  // 기대 출력: (null)

//     // (4) NULL 문자 ('\0') 찾기
//     printf("Test 4: %s\n", strrchr(s, '\0'));  // 기대 출력: ""

//     // (5) 빈 문자열에서 문자 찾기
//     char *empty = "";
//     printf("Test 5: %s\n", strrchr(empty, 'a'));  // 기대 출력: (null)
//     printf("Test 6: %s\n", strrchr(empty, '\0')); // 기대 출력: ""

//     return 0;
// }
