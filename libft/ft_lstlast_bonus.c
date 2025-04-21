/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:18:47 by sisung            #+#    #+#             */
/*   Updated: 2025/04/16 16:11:57 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// #include <stdio.h>

// int main()
// {
// 	int *v1 = malloc(sizeof(int));
// 	int *v2 = malloc(sizeof(int));
// 	int *v3 = malloc(sizeof(int));
// 	if (!v1 || !v2 || !v3)
// 		return (1);
// 	*v1 = 10;
// 	*v2 = 20;
// 	*v3 = 30;

// 	t_list *n1 = ft_lstnew(v1);
// 	t_list *n2 = ft_lstnew(v2);
// 	t_list *n3 = ft_lstnew(v3);

// 	n1->next = n2;
// 	n2->next = n3;

// 	t_list *last = ft_lstlast(n1);
// 	if (last)
// 		printf("Last node content: %d\n", *(int *)last->content);
// 	else
// 		printf("Last node is NULL");

// 	free(v1);
// 	free(v2);
// 	free(v3);

// 	t_list *tmp;
// 	while (n1)
// 	{
// 		tmp = n1->next;
// 		free(n1);
// 		n1 = tmp;
// 	}
// 	return 0;
// }