# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 14:11:38 by sisung            #+#    #+#              #
#    Updated: 2025/09/15 15:50:42 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 컴파일러 및 플래그
CC = cc
CFLAGS = -Wall -Wextra -Werror

# 프로그램 이름
NAME = so_long

# 소스 파일 경로
SRC_DIR = src
SRC = $(addprefix \
	  $(SRC_DIR)/, main.c \
	  			   map_parsing.c \
	  			   map_validation.c)

# 오브젝트 파일 경로
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

# Libft 디렉토리 및 라이브러리 경로
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# 헤더 파일 경로
INCLUDES = -Iinclude -I$(LIBFT_DIR)/include

# ========================================================================= #

# 최종 실행 파일 생성 규칙
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME) $(INCLUDES)

# Libft 라이브러리 빌드 (make -C를 사용하여 libft 디렉토리로 이동 후 빌드)
$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

# 소스 파일을 오브젝트 파일로 컴파일
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ========================================================================= #

# make clean: 오브젝트 파일 삭제
clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

# make fclean: 오브젝트 파일과 실행 파일 삭제
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

# make re: 전체 재빌드 (fclean 후 all)
re: fclean all

.PHONY: all clean fclean re
