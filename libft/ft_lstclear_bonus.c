/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:12:31 by sisung            #+#    #+#             */
/*   Updated: 2025/04/17 16:31:49 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}

// #include <stdio.h>

// void del(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	int *val1 = malloc(sizeof(int));
// 	int *val2 = malloc(sizeof(int));
// 	int *val3 = malloc(sizeof(int));
// 	*val1 = 1;
// 	*val2 = 2;
// 	*val3 = 3;

// 	// === 테스트 1: 일반 리스트 삭제 ===
// 	t_list	*head = ft_lstnew(val1);
// 	head->next = ft_lstnew(val2);
// 	head->next->next = ft_lstnew(val3);

// 	printf("Before clear:\n");
// 	t_list *tmp = head;
// 	while (tmp)
// 	{
// 		printf("Node content: %d\n", *(int *)tmp->content);
// 		tmp = tmp->next;
// 	}

// 	ft_lstclear(&head, del);

// 	if (head == NULL)
// 		printf("After clear: head is NULL ✅\n");
// 	else
// 		printf("After clear: head is NOT NULL ❌\n");

// 	printf("===== 테스트 1: lst == NULL =====\n");
// 	ft_lstclear(NULL, del);  // 아무 동작 없이 종료돼야 함
// 	printf("PASS ✅\n\n");

// 	printf("===== 테스트 2: *lst == NULL =====\n");
// 	t_list *null_head = NULL;
// 	ft_lstclear(&null_head, del);  // 역시 문제 없이 종료돼야 함
// 	printf("PASS ✅\n\n");

// 	printf("===== 테스트 3: del == NULL =====\n");
// 	int *value = malloc(sizeof(int));
// 	*value = 42;
// 	t_list *head = ft_lstnew(value);

// 	// del이 NULL이면 함수가 바로 return 해야 함 (free 호출 없이)
// 	ft_lstclear(&head, NULL);

// 	// 이후 메모리 누수는 남지만, crash는 없어야 함
// 	printf("PASS (crash 없음) ✅\n");

// 	// 메모리 수동 해제 (위에서 clear 실패했으므로 직접 해제)
// 	free(value);
// 	free(head);

// 	return 0;
// }