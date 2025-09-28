/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:23:30 by sisung            #+#    #+#             */
/*   Updated: 2025/09/25 16:53:28 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_pos	dequeue(t_qlist **queue)
{
	t_qlist	*temp;
	t_pos	pos;

	temp = *queue;
	pos = temp->pos;
	*queue = temp->next;
	free(temp);
	return (pos);
}

bool	enqueue(t_qlist **queue, t_pos pos)
{
	t_qlist	*new_node;
	t_qlist	*temp;

	new_node = malloc(sizeof(t_qlist));
	if (!new_node)
		return (false);
	new_node->pos = pos;
	new_node->next = NULL;
	if (*queue == NULL)
		*queue = new_node;
	else
	{
		temp = *queue;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return (true);
}

char	**map_copy_duplicate_fail(char **map_copy, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(map_copy[j]);
		j++;
	}
	free(map_copy);
	return (NULL);
}

bool	free_map_and_return_false(char **map_copy)
{
	free_map(map_copy);
	return (false);
}

bool	free_map_and_dequeue_and_return_false(char **m_c, t_qlist *q)
{
	free_map(m_c);
	while (q)
		dequeue(&q);
	return (false);
}
