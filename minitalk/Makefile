# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/02 17:32:43 by sisung            #+#    #+#              #
#    Updated: 2025/09/07 19:00:31 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- 컴파일러 및 플래그 ---
CC				= cc
CFLAGS			= -Wall -Wextra -Werror

# --- 디렉토리 설정 ---
SRC_DIR			= src/
BONUS_DIR		= src/bonus/
INC_DIR			= include/
LIBFT_DIR		= libft/
OBJS_DIR		= .objs/

# --- 필수 파트 (Mandatory) ---
MANDATORY_SRCS	= $(SRC_DIR)client.c $(SRC_DIR)server.c
MANDATORY_OBJS	= $(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(MANDATORY_SRCS))
MANDATORY_EXE	= client server

# --- 보너스 파트 (Bonus) ---
BONUS_SRCS		= $(BONUS_DIR)client_bonus.c $(BONUS_DIR)server_bonus.c
BONUS_OBJS		= $(patsubst $(BONUS_DIR)%.c, $(OBJS_DIR)%.o, $(BONUS_SRCS))
BONUS_EXE		= client_bonus server_bonus

# --- 메인 타겟 ---
all: mandatory

mandatory: $(MANDATORY_EXE)

bonus: $(BONUS_EXE)

# --- 컴파일 규칙 ---
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)include/ -c $< -o $@

$(OBJS_DIR)%.o: $(BONUS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)include/ -c $< -o $@

# --- 링크 규칙 ---
client: $(OBJS_DIR)client.o libft
	$(CC) $(CFLAGS) $(OBJS_DIR)client.o -L$(LIBFT_DIR) -lft -o client

server: $(OBJS_DIR)server.o libft
	$(CC) $(CFLAGS) $(OBJS_DIR)server.o -L$(LIBFT_DIR) -lft -o server

client_bonus: $(OBJS_DIR)client_bonus.o libft
	$(CC) $(CFLAGS) $(OBJS_DIR)client_bonus.o -L$(LIBFT_DIR) -lft -o client_bonus

server_bonus: $(OBJS_DIR)server_bonus.o libft
	$(CC) $(CFLAGS) $(OBJS_DIR)server_bonus.o -L$(LIBFT_DIR) -lft -o server_bonus

libft:
	$(MAKE) -C $(LIBFT_DIR)

# --- 정리 타겟 ---
clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(MANDATORY_EXE) $(BONUS_EXE)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all mandatory bonus clean fclean re libft
