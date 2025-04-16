/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:58:39 by sisung            #+#    #+#             */
/*   Updated: 2025/04/16 13:31:25 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>

// void print_list(t_list *lst)
// {
// 	while (lst)
// 	{
// 		printf("%s -> ", (char *)lst->content);
// 		lst = lst->next;
// 	}
// 	printf("NULL\n");
// }

// int main()
// {
// 	t_list	*head = NULL;
// 	t_list	*node1 = ft_lstnew("world");
// 	t_list	*node2 = ft_lstnew("hello");

// 	ft_lstadd_front(&head, node1); // world
// 	ft_lstadd_front(&head, node2); // hello -> world

// 	print_list(head);

// 	return (0);
// }