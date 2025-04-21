/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:07:26 by sisung            #+#    #+#             */
/*   Updated: 2025/04/17 13:39:02 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// #include <stdio.h>

// static void del_content(void *ptr)
// {
// 	printf("del_content: freeing %p\n", ptr);
// 	free(ptr);
// }

// int main()
// {
// 	t_list *node;
// 	t_list *next_node;
// 	char *data;

// 	node = malloc(sizeof(t_list));
// 	if (!node)
// 		return (1);
// 	data = malloc(32);
// 	if (!data)
// 	{
// 		free(node);
// 		return (1);
// 	}
// 	next_node = malloc(sizeof(t_list));
// 	if (!next_node)
// 	{
// 		free(data);
// 		free(node);
// 		return (1);
// 	}

// 	node->content = data;
// 	node->next = next_node;

// 	printf("Before ft_lstdelone:\n");
// 	printf("  node        = %p\n", node);
// 	printf("  node->content = %p\n", node->content);
// 	printf("  node->next    = %p\n", node->next);

// 	/* 3. 노드 하나만 삭제 */
// 	ft_lstdelone(node, del_content);

// 	printf("After ft_lstdelone:\n");
// 	printf("  (node와 content는 해제됨)\n");
// 	printf("  next_node still exists at %p\n", next_node);

// 	/* 4. 할당해 둔 다음 노드 정리 */
// 	free(next_node);
// 	return (0);
// }