# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/11 15:07:19 by sisung            #+#    #+#              #
#    Updated: 2025/08/06 21:45:49 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes

# ===== main program: push_swap =====
NAME = push_swap

SRCS = push_swap.c \
	   parsing.c \
	   utils.c \
	   input_validation.c \
	   ft_split.c \
	   stack_init_free.c \
	   stack_ops.c \
	   stack_utils.c \
	   swap.c \
	   push.c \
	   rotate.c \
	   reverse_rotate.c

OBJS = $(SRCS:.c=.o)

# ===== test stack program =====
TEST_STACK_NAME = test_stack

TEST_STACK_SRCS = tests/test_stack.c \
				  stack_init_free.c \
				  stack_ops.c \
				  stack_utils.c \
				  utils.c

TEST_STACK_OBJS = $(TEST_STACK_SRCS:.c=.o)

# ===== test function program =====
TEST_FUNC_NAME = test_func

TEST_FUNC_SRCS = tests/test_func.c \
				 swap.c \
				 push.c \
				 rotate.c \
				 reverse_rotate.c \
				 stack_init_free.c \
				 stack_ops.c \
				 stack_utils.c \
				 utils.c

TEST_FUNC_OBJS = $(TEST_FUNC_SRCS:.c=.o)

.PHONY: all clean fclean re

# 'make'만 실행하면 메인 프로그램(push_swap)이 빌드됨.
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# 'make test_stack'를 실행하면 테스트 프로그램(test_stack_program)이 빌드됨.
test_stack : $(TEST_STACK_NAME)

$(TEST_STACK_NAME): $(TEST_STACK_OBJS)
	$(CC) $(CFLAGS) $(TEST_STACK_OBJS) -o $(TEST_STACK_NAME)

# 'make test_func'를 실행하면 테스트 프로그램(test_func_program)이 빌드됨.
test_func : $(TEST_FUNC_NAME)

$(TEST_FUNC_NAME): $(TEST_FUNC_OBJS)
	$(CC) $(CFLAGS) $(TEST_FUNC_OBJS) -o $(TEST_FUNC_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_STACK_OBJS) $(TEST_FUNC_OBJS)

fclean: clean
	rm -f $(NAME) $(TEST_STACK_NAME) $(TEST_FUNC_NAME)

re: fclean all