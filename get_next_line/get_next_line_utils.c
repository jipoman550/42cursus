/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:45:45 by sisung            #+#    #+#             */
/*   Updated: 2025/05/27 18:03:41 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t		i;
	char	*dup;

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

char	*ft_strchr(const char *s, int c)
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

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		cnt++;
		s++;
	}
	return (cnt);
}

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
