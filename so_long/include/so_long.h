/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:11:26 by sisung            #+#    #+#             */
/*   Updated: 2025/09/13 15:38:56 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONH_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"

# include <fcntl.h> // open(), O_RDONLY
# include <stdlib.h> // free()

char	**parse_map(char *file_path);

#endif
