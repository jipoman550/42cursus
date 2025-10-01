/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:11:26 by sisung            #+#    #+#             */
/*   Updated: 2025/10/01 10:37:29 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"

# include "mlx.h"

# include <fcntl.h> // open(), O_RDONLY
# include <stdlib.h> // free(), exit()
# include <unistd.h>
# include <stdbool.h>

# define TILE_SIZE 64

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	size_t	win_width;
	size_t	win_height;
	size_t	player_x;
	size_t	player_y;
	size_t	moves;
	size_t	collectables;
} t_game;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_qlist
{
	t_pos			pos;
	struct s_qlist	*next;
}	t_qlist;

//void	ft_error(t_game *game, const char *msg);
void	free_map(char **map);

char	**parse_map(char *file_path);

size_t	get_map_width(char **map);
size_t	get_map_height(char **map);

bool	map_validation(char **map);

bool	check_valid_path(char **map, size_t total_c);

t_pos	dequeue(t_qlist **queue);
bool	enqueue(t_qlist **queue, t_pos pos);
char	**map_copy_duplicate_fail(char **map_copy, size_t i);
bool	free_map_and_return_false(char **map_copy);
bool	free_map_and_dequeue_and_return_false(char **m_c, t_qlist *q);

#endif
