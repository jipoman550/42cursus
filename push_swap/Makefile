# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/11 15:07:19 by sisung            #+#    #+#              #
#    Updated: 2025/08/05 16:02:04 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinlcudes

# ===== main program: push_swap =====
NAME = push_swap

SRCS = push_swap.c \
	   parsing.c \
	   utils.c \
	   input_validation.c \
	   ft_split.c \
	   stack_init_free.c \
	   stack_ops.c \
	   stack_utils.c

OBJS = $(SRCS:.c=.o)

# ===== test stack program =====
TEST_NAME = test_stack

TEST_SRCS = tests/test_stack.c \
			stack_init_free.c \
			stack_ops.c \
			stack_utils.c \
			utils.c

TEST_OBJS = $(TEST_SRCS:.c=.o)

.PHONY: all clean fclean re

# 'make'만 실행하면 메인 프로그램(push_swap)이 빌드됨.
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# 'make test'를 실행하면 테스트 프로그램(test_stack_program)이 빌드됨.
test: $(TEST_NAME)

$(TEST_NAME): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -o $(TEST_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all