# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/10 13:32:58 by sisung            #+#    #+#              #
#    Updated: 2025/06/03 09:38:22 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -I./libft

NAME		=	libftprintf.a

SRCS		=	ft_printf.c \
				ft_conversions.c \
				ft_convert_char.c \
				ft_convert_string.c \
				ft_convert_pointer.c \
				ft_convert_decimal.c \
				ft_convert_unsigned.c \
				ft_convert_hex.c \
				ft_convert_percent.c \
				ft_utils.c \
				libft/ftp_putchar_fd.c \
				libft/ftp_putnbr_fd.c \
				libft/ftp_putstr_fd.c \
				libft/ftp_strlen.c

OBJS		=	$(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c ft_printf.h libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all