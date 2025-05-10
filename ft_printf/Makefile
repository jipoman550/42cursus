# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/10 13:32:58 by sisung            #+#    #+#              #
#    Updated: 2025/05/10 17:28:24 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Complier & flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I./libft

# libft submodule
LIBFTDIR	=	libft
LIBFT		=	$(LIBFTDIR)/libft.a

# Target library name
NAME		=	libftprintf.a

# Progect source files (madatory .c only; tests/ 제외)
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

# Phony targets
.PHONY: all clean fclean re

# Default rule: build libftprintf.a (after building libft)
all: $(LIBFT) $(NAME)

# Rule to build libft.a using its own Makefile
$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

# Archive project objects into libftprintf.a
# (unnecessary if OBJS are up-to-date -> no relink)
$(NAME): $(LIBFT) $(OBJS)
	@cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

# Compile each source file
# - Depend on ft_printf.h and libft headers
%.o: %.c ft_printf.h libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

# clean: remove .o and delegate to libft
clean:
	$(MAKE) -C $(LIBFTDIR) clean
	rm -f $(OBJS)

# fclean: clean + remove the library + delegate to libft
fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(NAME)

# re: full rebuild
re: fclean all