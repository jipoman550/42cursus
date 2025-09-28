/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:51:30 by sisung            #+#    #+#             */
/*   Updated: 2025/09/25 16:56:18 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_pos	find_player_pos(char **map)
{
	t_pos	pos;
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				pos.y = i;
				pos.x = j;
				return (pos);
			}
			j++;
		}
		i++;
	}
	pos.x = -1;
	return (pos);
}

static char	**copy_map(char **map)
{
	char	**map_copy;
	size_t	i;

	i = 0;
	while (map[i])
		i++;
	map_copy = malloc(sizeof(char *) * (i + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
			return (map_copy_duplicate_fail(map_copy, i));
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

static bool	explore_neighbors(char **map, t_qlist **queue, t_pos current)
{
	t_pos	neighbors[4];
	size_t	i;
	t_pos	n_pos;

	neighbors[0].x = current.x;
	neighbors[0].y = current.y - 1;
	neighbors[1].x = current.x;
	neighbors[1].y = current.y + 1;
	neighbors[2].x = current.x - 1;
	neighbors[2].y = current.y;
	neighbors[3].x = current.x + 1;
	neighbors[3].y = current.y;
	i = 0;
	while (i < 4)
	{
		n_pos = neighbors[i];
		if (n_pos.y >= 0 && n_pos.x >= 0 && map[n_pos.y] && map[n_pos.y]
			&& map[n_pos.y][n_pos.x] != '1' && map[n_pos.y][n_pos.x])
		{
			if (!enqueue(queue, n_pos))
				return (false);
		}
		i++;
	}
	return (true);
}

static bool	run_bfs(char **map_copy, t_qlist **queue, size_t *found_c, bool *e)
{
	t_pos	current;

	while (*queue)
	{
		current = dequeue(queue);
		if (map_copy[current.y][current.x] == '1')
			continue ;
		if (map_copy[current.y][current.x] == 'C')
			(*found_c)++;
		if (map_copy[current.y][current.x] == 'E')
			*e = true;
		map_copy[current.y][current.x] = '1';
		if (!explore_neighbors(map_copy, queue, current))
			return (false);
	}
	return (true);
}

bool	check_valid_path(char **map, size_t total_c)
{
	char	**map_copy;
	t_pos	current;
	t_qlist	*queue;
	size_t	found_c;
	bool	exit_reachable;

	map_copy = copy_map(map);
	if (!map_copy)
		return (false);
	current = find_player_pos(map_copy);
	if (current.x == -1)
		free_map_and_return_false(map_copy);
	queue = NULL;
	if (!enqueue(&queue, current))
		free_map_and_return_false(map_copy);
	found_c = 0;
	exit_reachable = false;
	if (!run_bfs(map_copy, &queue, &found_c, &exit_reachable))
		free_map_and_dequeue_and_return_false(map_copy, queue);
	free_map(map_copy);
	if (found_c != total_c || !exit_reachable)
		return (false);
	return (true);
}
