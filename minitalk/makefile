# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/02 17:32:43 by sisung            #+#    #+#              #
#    Updated: 2025/09/04 19:22:06 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = server client

SRC_DIR = src
SRCS = $(SRC_DIR)/server.c\
       $(SRC_DIR)/client.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_PATH = -L$(LIBFT_DIR) -lft

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

server: $(SRC_DIR)/server.o $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_DIR)/server.o $(LIBFT_PATH) -o server

client: $(SRC_DIR)/client.o $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_DIR)/client.o $(LIBFT_PATH) -o client

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o:%.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR)/include -I$(SRC_DIR) -Iinclude -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
