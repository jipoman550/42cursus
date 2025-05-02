# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 16:22:45 by sisung            #+#    #+#              #
#    Updated: 2025/05/02 20:08:10 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 컴파일러 설정
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -I. # 과제제출 할 때 옵션들(-g, -I)같은 것들은 제거해야함.

# 실행 파일 이름
NAME	= ft_printf_test

# 소프 파일 목록
SRC		=	ft_printf.c \
			ft_conversions.c \
			ft_convert_char.c \

# 오브젝트 파일 이름 (SRC의 .c -> .o)
OBJS	= $(SRC:.c=.o)

# 테스트 main 파일 (하나씩 교체 가능)
TEST_DIR = tests
TEST_SRC = $(TEST_DIR)/main_c.c # 요기를 바꾸면 다른 테스트로 교체 가능
TEST_OBJS = $(TEST_SRC:.c=.o)

# 기본 타켓: all -> $(NAME)
all: $(NAME)

# 실행 파일 빌드
$(NAME): $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# .c -> .o 컴파일 룰
# ft_printf.h가 수정되면 관련 .o들도 재컴파일
%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

# 테스트용 오브젝트 컴파일 룰
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

# 중간파일 삭제
clean:
	rm -f $(OBJS) $(TEST_OBJS)

# 중간 파일 삭제 + 실행 파일 삭제
fclean: clean
	rm -f $(NAME)

# 다시 빌드
re: fclean all

.PHONY: all clean fclean re