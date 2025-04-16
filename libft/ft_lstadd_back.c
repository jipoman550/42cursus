/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:19:40 by sisung            #+#    #+#             */
/*   Updated: 2025/04/16 18:41:50 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

// #include <stdio.h>

// int main()
// {
// 	t_list *list = NULL;
// 	t_list *node1;
// 	t_list *node2;
// 	t_list *node3;
// 	t_list *temp;

// 	node1 = ft_lstnew("First");
// 	node2 = ft_lstnew("Second");
// 	node3 = ft_lstnew("Third");

// 	ft_lstadd_back(&list, node1);
// 	ft_lstadd_back(&list, node2);
// 	ft_lstadd_back(&list, node3);

// 	printf("리스트 출력:\n");
// 	temp = list;
// 	while (temp)
// 	{
// 		printf("%s\n", (char *)temp->content);
// 		temp = temp->next;
// 	}

// 	temp = list;
// 	t_list *next;
// 	while (temp)
// 	{
// 		next = temp->next;
// 		free(temp);
// 		temp = next;
// 	}

// 	return 0;
// }