/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:11:26 by sisung            #+#    #+#             */
/*   Updated: 2025/09/15 15:59:33 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONH_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"

# include <fcntl.h> // open(), O_RDONLY
# include <stdlib.h> // free(), exit()
# include <unistd.h>
# include <stdbool.h>

typedef struct	s_pos
{
	int	x;
	int	y;
} t_pos;

typedef struct	s_list
{
	t_pos			pos;
	struct s_list	*next;
} t_list;

char	**parse_map(char *file_path);
void	ft_error(void);

#endif
