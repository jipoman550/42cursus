# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/11 15:07:19 by sisung            #+#    #+#              #
#    Updated: 2025/08/26 13:31:57 by sisung           ###   ########.fr        #
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
	   reverse_rotate.c \
	   sort_small.c \
	   src/sort_big.c

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

# ===== test sort program =====
TEST_SORT_NAME = test_sort

TEST_SORT_SRCS = tests/test_sort.c \
				 stack_init_free.c \
				 stack_ops.c \
				 input_indexing.c \
				 utils.c

TEST_SORT_OBJS = $(TEST_SORT_SRCS:.c=.o)

# ===== test sort small program =====
TEST_SORT_SMALL_NAME = test_sort_small

TEST_SORT_SMALL_SRCS = tests/test_sort_small.c \
		stack_init_free.c \
		stack_ops.c \
		stack_utils.c \
		input_indexing.c \
		utils.c \
		swap.c \
		push.c \
		rotate.c \
		reverse_rotate.c \
		sort_small.c

TEST_SORT_SMALL_OBJS = $(TEST_SORT_SMALL_SRCS:.c=.o)

# ===== test sort big program =====
TEST_SORT_BIG_NAME = test_sort_big
TEST_SORT_BIG_SRCS = tests/test_sort_big.c \
					 src/sort_big.c \
					 stack_init_free.c \
					 stack_utils.c \
					 input_indexing.c \
					 utils.c \
					 push.c \
					 rotate.c \
					 reverse_rotate.c \
					 swap.c \
					 stack_ops.c

TEST_SORT_BIG_OBJS = $(TEST_SORT_BIG_SRCS:.c=.o)

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

# 'make test_sort'를 실행하면 테스트 프로그램이 빌드됨
test_sort : $(TEST_SORT_NAME)

$(TEST_SORT_NAME): $(TEST_SORT_OBJS)
	$(CC) $(CFLAGS) $(TEST_SORT_OBJS) -o $(TEST_SORT_NAME)

# 'make test_sort_small'를 실행하면 테스트 프로그램이 빌드됨
test_sort_small : $(TEST_SORT_SMALL_NAME)

$(TEST_SORT_SMALL_NAME): $(TEST_SORT_SMALL_OBJS)
	$(CC) $(CFLAGS) $(TEST_SORT_SMALL_OBJS) -o $(TEST_SORT_SMALL_NAME)

# 'make test_sort_big'를 실행하면 테스트 프로그램이 빌드됨
test_sort_big : $(TEST_SORT_BIG_NAME)

$(TEST_SORT_BIG_NAME): $(TEST_SORT_BIG_OBJS)
	$(CC) $(CFLAGS) $(TEST_SORT_BIG_OBJS) -o $(TEST_SORT_BIG_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_STACK_OBJS) $(TEST_FUNC_OBJS) $(TEST_SORT_OBJS) $(TEST_SORT_SMALL_OBJS) $(TEST_SORT_BIG_OBJS)

fclean: clean
	rm -f $(NAME) $(TEST_STACK_NAME) $(TEST_FUNC_NAME) $(TEST_SORT_NAME) $(TEST_SORT_SMALL_NAME) $(TEST_SORT_BIG_NAME)

re: fclean all
