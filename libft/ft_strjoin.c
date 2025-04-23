/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:04:19 by sisung            #+#    #+#             */
/*   Updated: 2025/04/23 14:46:18 by sisung           ###   ########.fr       */
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
