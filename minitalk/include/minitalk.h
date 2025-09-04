/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:46:20 by sisung            #+#    #+#             */
/*   Updated: 2025/09/04 21:41:18 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <sys/types.h>

# include "ft_printf.h"
# include "libft.h"

struct	s_state {
	char	current_char;
	int		bit_count;
};

extern struct s_state	g_server_state;

#endif
