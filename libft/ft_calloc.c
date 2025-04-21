/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:28:27 by sisung            #+#    #+#             */
/*   Updated: 2025/04/18 17:07:01 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ret;

	if (nelem == 0 || elsize == 0)
		return (malloc(0));
	if (nelem > -1 / elsize)
		return (NULL);
	ret = (void *)malloc(nelem * elsize);
	if (!ret)
		return (NULL);
	ft_bzero(ret, nelem * elsize);
	return (ret);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main()
// {
// 	void *ptr;

// 	// 정상적인 할당
// 	ptr = ft_calloc(5, sizeof(int));
// 	if (ptr)
// 		printf("정상적으로 메모리 할당됨\n");
// 	free(ptr);

// 	// 오버플로우 발생 테스트
// 	size_t huge_nelem = (size_t)-1 / 2 + 1; // 오버플로우 유발 값
// 	size_t huge_elsize = 2;

// 	ptr = ft_calloc(huge_nelem, huge_elsize);
// 	if (!ptr)
// 		printf("ft____오버플로우로 인해 NULL 반환됨\n");

// 	ptr = calloc(huge_nelem, huge_elsize);
// 	if (!ptr)
// 		printf("ori____오버플로우로 인해 NULL 반환됨\n");

// 	return 0;
// }