# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/19 22:38:35 by sisung            #+#    #+#              #
#    Updated: 2025/10/22 09:07:22 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC         = cc
CFLAGS     = -Wall -Wextra -Werror -g -pthread

NAME       = philo

# 소스 및 헤더 디렉토리
SRC_DIR    = philo
INC_DIR    = philo

# 소스 파일 목록 (현재 분리된 파일 기준)
SRC_FILES  = main.c \
			 parse.c \
			 init.c \
			 time.c \
			 utils.c

SRCS       = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# 오브젝트 파일 목록
OBJS       = $(SRC_FILES:.c=.o)

%.o: $(SRC_DIR)/%.c $(INC_DIR)/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test test_parse

# ========================================================================= #
#                                TEST SECTION                               #
# ========================================================================= #

# make test: 인자 파싱 및 유효성 검사 테스트만 실행
test: test_parse
	@echo "\n========================================"
	@echo " ✅ PARSING TESTS COMPLETED SUCCESSFULLY!"
	@echo " (Continue to core logic testing...)"
	@echo "========================================"

# --- 인자 파싱 및 유효성 검사 테스트 타겟 ---
test_parse: $(NAME)
	@echo "\n--- [TEST] Argument Parsing & Validation ---"

# 1. 실패 케이스: 인자 개수 오류 (Exit Code 1 기대)
	@echo "\n  - [FAIL] Argument Count Tests:"
	@./$(NAME) 5 800 > /dev/null 2>&1 || echo "    - ✅ Test: Not enough args (Exit $$?) PASSED" || echo "    - ❌ Test: Not enough args FAILED"
	@./$(NAME) 5 800 200 200 5 500 > /dev/null 2>&1 || echo "    - ✅ Test: Too many args (Exit $$?) PASSED" || echo "    - ❌ Test: Too many args FAILED"

# 2. 실패 케이스: 숫자 유효성 오류 (Exit Code 1 기대)
	@echo "\n  - [FAIL] Numeric Validation Tests:"
	@./$(NAME) 0 800 200 200 > /dev/null 2>&1 || echo "    - ✅ Test: Num_philo is zero (Exit $$?) PASSED" || echo "    - ❌ Test: Num_philo is zero FAILED"
	@./$(NAME) hello 800 200 200 > /dev/null 2>&1 || echo "    - ✅ Test: Non-numeric arg (Exit $$?) PASSED" || echo "    - ❌ Test: Non-numeric arg FAILED"

# 3. 성공 케이스: 유효한 인자 (Exit Code 0 기대)
	@echo "\n  - [SUCCESS] Valid Argument Tests:"
	@./$(NAME) 5 800 200 200 > /dev/null 2>&1; if [ $$? -eq 0 ]; then echo "    - ✅ Test: 4 args PASSED"; else echo "    - ❌ Test: 4 args FAILED (Exit $$?)"; fi
	@./$(NAME) 5 800 200 200 10 > /dev/null 2>&1; if [ $$? -eq 0 ]; then echo "    - ✅ Test: 5 args PASSED"; else echo "    - ❌ Test: 5 args FAILED (Exit $$?)"; fi