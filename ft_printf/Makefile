# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/10 13:32:58 by sisung            #+#    #+#              #
#    Updated: 2025/05/14 17:36:11 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I./libft

LIBFTDIR	=	libft
LIBFT		=	$(LIBFTDIR)/libft.a

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
				ft_utils.c

OBJS		=	$(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME): $(LIBFT) $(OBJS)
	@cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

%.o: %.c ft_printf.h libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all