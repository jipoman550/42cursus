/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:38:41 by sisung            #+#    #+#             */
/*   Updated: 2025/04/16 14:13:36 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	cnt;

	cnt = 0;
	while (lst)
	{
		cnt++;
		lst = lst->next;
	}
	return (cnt);
}

// #include <stdio.h>

// int main()
// {
// 	t_list *head = ft_lstnew("node1");
// 	head->next = ft_lstnew("node2");
// 	head->next->next = ft_lstnew("node3");

// 	int size = ft_lstsize(head);
// 	printf("리스트의 노드 수: %d\n", size);  // 출력: 3

// 	// 메모리 해제 (선택적)
// 	t_list *tmp;
// 	while (head)
// 	{
// 		tmp = head->next;
// 		free(head);
// 		head = tmp;
// 	}
// 	return 0;
// }