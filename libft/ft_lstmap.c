/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:54:49 by sisung            #+#    #+#             */
/*   Updated: 2025/04/17 20:48:57 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*cur;

	new = lst;
	while (lst)
	{
		cur = ft_lstnew(f(new->content));
		if (!cur)
		{
			ft_lstclear(&lst, del);
			return (void *) (NULL);
		}
		ft_lstadd_back(&lst, new);
		lst = lst->next;
	}
	return (new);
}
