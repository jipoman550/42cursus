/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:28:17 by sisung            #+#    #+#             */
/*   Updated: 2025/04/10 15:41:06 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_split_array(char **arr, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char		*str;
	size_t		i;

	str = (char *)malloc(n + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**split_words(char const *s, char c, char **arr)
{
	size_t		i;
	size_t		len;
	const char	*word_start;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			word_start = s;
			len = 0;
			while (s[len] && s[len] != c)
				len++;
			arr[i] = ft_strndup(word_start, len);
			if (!arr[i])
				return (free_split_array(arr, i));
			i++;
			s += len;
		}
	}
	arr[i] = NULL;
	return (arr);
}

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	size_t		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	return (split_words(s, c, arr));
}

// #include <stdio.h>

// void test_split(const char *s, char c)
// {
//     char **result = ft_split(s, c);
//     size_t i = 0;

//     printf("Input: \"%s\" | Delimiter: '%c'\n", s ? s : "(null)", c);
//     if (!result)
//     {
//         printf("ft_split returned NULL\n\n");
//         return;
//     }

//     while (result[i])
//     {
//         printf("result[%d] = \"%s\"\n", i, result[i]);
//         i++;
//     }
//     printf("\n");

//     i = 0;
//     while (result[i])
//     {
//         free(result[i]);
//         i++;
//     }
//     free(result);
// }

// size_t main()
// {
//     printf("===== Normal Cases =====\n");
//     test_split("hello world this is test", ' ');  // 일반적인 단어 분할
//     test_split("hello/world/bro", '/');          // '/' 기준 단어 분할
//     test_split("apple,banana,grape", ',');       // ',' 기준 분할

//     printf("===== Edge Cases =====\n");
//     test_split("", ' ');                         // 빈 문자열
//     test_split("////", '/');                     // 구분자로만 이루어진 문자열
//     test_split("hello", ' ');                    // 구분자가 없는 경우
//     test_split("   spaced   words   ", ' ');     // 공백이 앞뒤에 있는 경우
//     test_split("split  test   case", ' ');       // 연속된 구분자 처리
//     test_split("endswithdelimiter/", '/');       // 문자열이 구분자로 끝나는 경우
//     test_split("/startswithdelimiter", '/');     // 문자열이 구분자로 시작하는 경우
//     test_split("mid//dle", '/');                 // 중간에 연속된 구분자가 있는 경우
//     test_split("justoneword", '/');              // 분리할 단어가 하나뿐인 경우

//     printf("===== Special Cases =====\n");
//     test_split(NULL, ' ');                       // NULL 입력 처리

//     return 0;
// }