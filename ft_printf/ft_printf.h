/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:50:26 by sisung            #+#    #+#             */
/*   Updated: 2025/05/09 17:18:08 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);

int		handle_conversion(char conversion, va_list args);

int		convert_char(va_list args);
int		convert_string(va_list args);
int		convert_pointer(va_list args);
int		convert_decimal(va_list args);
int		convert_unsigned(va_list args);
int		convert_hex(char conversion, va_list args);
int		convert_percent(void);

int		decimal_len(int num);
int		unsigned_len(unsigned int num);
void	ft_putnbr_unsigned_fd(unsigned int n, int fd);
int		hex_len(unsigned long num);
void	print_hex(unsigned long num, int is_upper);

#endif