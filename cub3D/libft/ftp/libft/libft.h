/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:06:28 by sisung            #+#    #+#             */
/*   Updated: 2025/08/01 18:22:40 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int		ftp_putchar_fd(char c, int fd);
int		ftp_putnbr_fd(int n, int fd);
int		ftp_putstr_fd(char *s, int fd);
size_t	ftp_strlen(const char *s);

#endif
