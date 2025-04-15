/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:27:57 by sisung            #+#    #+#             */
/*   Updated: 2025/04/15 20:54:31 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// #include <stdio.h>

// int main(void)
// {
// 	t_list *node;

// 	node = ft_lstnew("abcdef");

// 	if (node == NULL)
// 	{
// 		printf("Node creation failed.\n");
// 		return (1);
// 	}

// 	printf("Content: %s\n", (char *)node->content);
// 	printf("Next: %p\n", (void *)node->next);

// 	return (0);
// }
