/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:17:05 by sisung            #+#    #+#             */
/*   Updated: 2025/04/14 15:15:01 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>

// void INDEX_COMP_PLUS(unsigned int i, char *str)
// {
// 	*str = *str + i;
// }

// void INDEX_COMP_MINUS(unsigned int i, char *str)
// {
// 	*str = *str - i;
// }

// int main()
// {
// 	char str[] = "abc";
// 	ft_striteri(str, INDEX_COMP_PLUS);
// 	printf("%s\n", str);

// 	ft_striteri(str, INDEX_COMP_MINUS);
// 	printf("%s\n", str);
// 	return 0;
// }