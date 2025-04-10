/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:16:04 by sisung            #+#    #+#             */
/*   Updated: 2025/04/10 17:10:52 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ret = ret * 10 + nptr[i] - '0';
		i++;
	}
	return (sign * ret);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main()
// {
// 	char *test1 = "123";
// 	char *test2 = "-42";
// 	char *test3 = " 456";
// 	char *test4 = "+++---78";
// 	char *test5 = "-99";
// 	char *test6 = "42abc";
// 	char *test7 = "999999999999";
// 	char *test8 = "2147483647";   // INT_MAX
// 	char *test9 = "2147483648";   // INT_MAX 초과
// 	char *test10 = "-2147483648"; // INT_MIN
// 	char *test11 = "-2147483649"; // INT_MIN 초과

// 	printf("ft_atoi : %d\n", ft_atoi(test1));
// 	printf("atoi : %d\n", atoi(test1));

// 	printf("ft_atoi : %d\n", ft_atoi(test2));
// 	printf("atoi : %d\n", atoi(test2));

// 	printf("ft_atoi : %d\n", ft_atoi(test3));
// 	printf("atoi : %d\n", atoi(test3));

// 	printf("ft_atoi : %d\n", ft_atoi(test4));
// 	printf("atoi : %d\n", atoi(test4));

// 	printf("ft_atoi : %d\n", ft_atoi(test5));
// 	printf("atoi : %d\n", atoi(test5));

// 	printf("ft_atoi : %d\n", ft_atoi(test6));
// 	printf("atoi : %d\n", atoi(test6));

// 	printf("ft_atoi : %d\n", ft_atoi(test7));
// 	printf("atoi : %d\n", atoi(test7));

// 	printf("ft_atoi : %d\n", ft_atoi(test8));
// 	printf("atoi : %d\n", atoi(test8));

// 	printf("ft_atoi : %d\n", ft_atoi(test9));
// 	printf("atoi : %d\n", atoi(test9));

// 	printf("ft_atoi : %d\n", ft_atoi(test10));
// 	printf("atoi : %d\n", atoi(test10));

// 	printf("ft_atoi : %d\n", ft_atoi(test11));
// 	printf("atoi : %d\n", atoi(test11));

// 	return 0;
// }