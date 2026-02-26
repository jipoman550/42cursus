# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/19 23:25:02 by sisung            #+#    #+#              #
#    Updated: 2026/02/19 23:25:05 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
NAME_BONUS	= cub3D_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

INCLUDES	= -I. -I./includes -I./minilibx-linux -I./libft

# Libft
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

# MinilibX
MLX_DIR		= ./minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -lbsd

# Sources
SRCS_DIR	= srcs

SRCS		= $(SRCS_DIR)/main.c \
			$(SRCS_DIR)/parsing.c \
			$(SRCS_DIR)/parsing_utils.c \
			$(SRCS_DIR)/input.c \
			$(SRCS_DIR)/init.c
OBJS		= $(SRCS:.c=.o)

SRCS_BONUS	= $(SRCS_DIR)/main_bonus.c \
			$(SRCS_DIR)/parsing.c \
			$(SRCS_DIR)/parsing_utils.c \
			$(SRCS_DIR)/input.c \
			$(SRCS_DIR)/init.c
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

# Test
TEST_DIR	= tests
TEST_NAME	= test_parsing
TEST_SRCS	= $(TEST_DIR)/test_parsing.c \
			$(SRCS_DIR)/parsing.c \
			$(SRCS_DIR)/parsing_utils.c
TEST_OBJS	= $(TEST_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX_FLAGS) -o $(NAME_BONUS)

$(LIBFT):
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make -C $(LIBFT_DIR) bonus; \
	else \
		echo "Error: libft directory not found."; \
		exit 1; \
	fi

$(MLX):
	@if [ -d "$(MLX_DIR)" ]; then \
		make -C $(MLX_DIR); \
	else \
		echo "Error: minilibx-linux directory not found."; \
		exit 1; \
	fi

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: $(LIBFT) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIBFT) -lm -o $(TEST_NAME)
	@echo ""
	@echo "🚀 Running parsing tests..."
	@echo ""
	@./$(TEST_NAME)
	@$(RM) $(TEST_NAME)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) $(TEST_OBJS)
	@if [ -d "$(LIBFT_DIR)" ]; then make -C $(LIBFT_DIR) clean; fi
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS) $(TEST_NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then make -C $(LIBFT_DIR) fclean; fi

re: fclean all

.PHONY: all clean fclean re bonus test