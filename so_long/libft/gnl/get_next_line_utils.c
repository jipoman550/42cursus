/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:45:45 by sisung            #+#    #+#             */
/*   Updated: 2025/09/13 16:07:02 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strndup(const char *s, size_t n)
{
	size_t		i;
	char		*dup;

	if (!s)
		return (NULL);
	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gnl_strchr(const char *s, int c)
{
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

size_t	gnl_strlen(const char *s)
{
	size_t	cnt;

	if (!s)
		return (0);
	cnt = 0;
	while (*s)
	{
		cnt++;
		s++;
	}
	return (cnt);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*strjoin;
	char	*p;

	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
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
