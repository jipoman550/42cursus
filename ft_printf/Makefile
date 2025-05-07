# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 16:22:45 by sisung            #+#    #+#              #
#    Updated: 2025/05/07 18:27:00 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 컴파일러 설정
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -I. -I./libft # 과제제출 할 때 테스트 케이스 옵션들(-g, -I)같은 것들은 제거해야함. 아니면 test 용 makefile과 제출용 makefile을 따로 만들던가

# libft 디렉토리 및 라이브러리
LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

# 실행 파일 이름
NAME	= ft_printf_test

# 소프 파일 목록
SRC		=	ft_printf.c \
			ft_conversions.c \
			ft_convert_char.c \
			ft_convert_string.c \
			ft_convert_pointer.c \
			ft_convert_decimal.c

# 테스트 main 파일 (하나씩 교체 가능)
TEST_DIR = tests
TEST_SRC = $(TEST_DIR)/main_d.c # 요기를 바꾸면 다른 테스트로 교체 가능

# 오브젝트 파일 목록
OBJS	 = $(SRC:.c=.o) $(TEST_SRC:.c=.o)

.PHONY: all clean fclean re

# 최상위 빌드: libft/libft.a → ft_printf_test
all: $(LIBFT) $(NAME)

# libft/libft.a 실제 룰
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# 실행 파일 빌드, 2) ft_printf_test 빌드 (libft.a 링크)
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# .c -> .o 컴파일 룰
# ft_printf.h가 수정되면 관련 .o들도 재컴파일
%.o: %.c ft_printf.h libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

# 테스트용 .c -> .o
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

# 중간파일 삭제
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

# 중간 파일 삭제 + 실행 파일 삭제
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# 다시 빌드
re: fclean all