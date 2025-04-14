/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:10:20 by sisung            #+#    #+#             */
/*   Updated: 2025/04/14 13:47:12 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen(s);
	if (!s || !f)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// #include <stdio.h>

// char INDEX_COMP_PLUS(unsigned int i, char c)
// {
// 	char str;
// 	str = c + i;
// 	return (str);
// }

// char INDEX_COMP_MINUS(unsigned int i, char c)
// {
// 	char str;
// 	str = c - i;
// 	return (str);
// }

// int main()
// {
// 	char *str = "abc";
// 	char *str2;
// 	str2 = ft_strmapi(str, INDEX_COMP_PLUS);
// 	printf("%s\n", str2);

// 	str2 = ft_strmapi(str, INDEX_COMP_MINUS);
// 	printf("%s\n", str2);
// 	return 0;
// }
