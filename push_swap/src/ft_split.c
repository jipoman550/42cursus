/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:06:32 by sisung            #+#    #+#             */
/*   Updated: 2025/08/06 21:32:51 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

size_t	count_words(const char *s, char c)
{
	size_t	count;

	if (!s)
		return (0);
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
