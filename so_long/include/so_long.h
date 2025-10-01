/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:11:26 by sisung            #+#    #+#             */
/*   Updated: 2025/10/01 13:27:46 by sisung           ###   ########.fr       */
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

# define WALL_PATH			"./textures/w.xpm"
# define FLOOR_PATH			"./textures/es.xpm"
# define EXIT_PATH			"./textures/exit.xpm"
# define COLLECT_PATH		"./textures/c.xpm"
# define PLAYER_RIGHT_PATH	"./textures/r.xpm"
# define PLAYER_LEFT_PATH	"./textures/l.xpm"
# define PLAYER_UP_PATH		"./textures/u.xpm"
# define PLAYER_DOWN_PATH	"./textures/d.xpm"

# define KEY_S	115
# define KEY_W	119
# define KEY_A	97
# define KEY_D	100

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

	void	*img_wall;
	void	*img_floor;
	void	*img_exit;
	void	*img_collect;
	void	*img_player_up;
	void	*img_player_down;
	void	*img_player_left;
	void	*img_player_right;
	size_t	player_direction;
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

void	load_images(t_game *game);
void	render_map(t_game *game);

#endif
