/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:04:14 by sisung            #+#    #+#             */
/*   Updated: 2025/04/17 19:32:13 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// #include <stdio.h>

// // content를 2배로 만드는 함수
// void	double_content(void *content)
// {
// 	if (content)
// 		*(int *)content *= 2;
// }

// // content를 출력하는 함수
// void	print_content(void *content)
// {
// 	if (content)
// 		printf("%d\n", *(int *)content);
// }

// int	main(void)
// {
// 	t_list *n1, *n2, *n3;
// 	int *a = malloc(sizeof(int));
// 	int *b = malloc(sizeof(int));
// 	int *c = malloc(sizeof(int));

// 	*a = 1;
// 	*b = 2;
// 	*c = 3;

// 	n1 = malloc(sizeof(t_list));
// 	n2 = malloc(sizeof(t_list));
// 	n3 = malloc(sizeof(t_list));

// 	n1->content = a;
// 	n1->next = n2;

// 	n2->content = b;
// 	n2->next = n3;

// 	n3->content = c;
// 	n3->next = NULL;

// 	// 원래 값 출력
// 	printf("Before:\n");
// 	ft_lstiter(n1, print_content);

// 	// 각 값을 2배로
// 	ft_lstiter(n1, double_content);

// 	// 변경된 값 출력
// 	printf("After:\n");
// 	ft_lstiter(n1, print_content);

// 	// 메모리 해제
// 	free(a);
// 	free(b);
// 	free(c);
// 	free(n1);
// 	free(n2);
// 	free(n3);

// 	return 0;
// }