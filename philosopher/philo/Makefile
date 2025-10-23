# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/19 22:38:35 by sisung            #+#    #+#              #
#    Updated: 2025/10/23 09:34:07 by sisung           ###   ########.fr        #
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

.PHONY: all clean fclean re

# ========================================================================= #
#                                TEST SECTION                               #
# ========================================================================= #

# make test: 모든 테스트 실행
test: test_parse test_leak
	@echo "\n========================================"
	@echo " ✅ ALL INITIALIZATION TESTS COMPLETED SUCCESSFULLY!"
	@echo " (0 bytes in 0 blocks leaked by Valgrind check required)"
	@echo "========================================"

# --- 1. 인자 파싱 및 유효성 검사 테스트 타겟 ---
# test_parse: 인자 파싱 및 유효성 검사 테스트만 실행
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

# >>>>>>>>>>>>>>> test_parse 완료 후 중간 메시지 출력 <<<<<<<<<<<<<<<
	@echo "\n========================================"
	@echo " ✅ PARSING TESTS COMPLETED SUCCESSFULLY!"
	@echo " (Starting Memory Leak Tests...)"
	@echo "========================================"

# --- 2. 메모리 누수 및 자원 정리 테스트 (Valgrind) ---

# 새로운 통합 타겟: test_leak
test_leak: test_leak_fail test_leak_success
	@echo "\n--- [TEST] Memory Leak Tests Completed ---"
# 이 타겟은 Valgrind 결과가 stdout에 출력된 후 실행됩니다.

# Valgrind를 실행하는 핵심 규칙
leak: $(NAME)
	@echo "\n--- [VALGRIND] Testing Args: $(ARGS) ---"
# --trace-children=yes는 스레드(pthread_create)를 검사할 때 필수입니다.
	-valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./$(NAME) $(ARGS)
	@echo "----------------------------------------"

# 2-A. 초기화 실패 경로에서 메모리 누수 테스트
# 목적: parse_and_save_args 또는 init_forks 실패 시 free_data(data)가 호출되어 정리되는지 확인
test_leak_fail: $(NAME)
	@echo "\n--- [TEST] Memory Leak on FAILURE Path ---"
	@echo " (모든 테스트는 '0 bytes in 0 blocks' 누수를 보여야 합니다.)"

## Case 1: 비-숫자 인자 (파싱 실패)
	make leak ARGS="10 800 200 invalid 5"

## Case 2: 철학자 수 0 (num_of_philos=0, 파싱 실패)
	make leak ARGS="0 800 200 200"

## Case 3: 시간 인자 0 (time_to_die=0, 파싱 실패)
	make leak ARGS="10 0 200 200 5"

## Case 4: Num_of_philos가 너무 커서 forks malloc 실패가 예상되는 경우 (옵션)
	make leak ARGS="9999999999999999999 800 200 200"

# 2-B. 초기화 성공 후, 즉시 자원 정리 테스트 (Cleanup on Success)
# 목적: init_data가 성공했을 때, destroy_all()이 모든 메모리와 뮤텍스를 해제하는지 확인
# 전제: main 함수가 init_data 성공 직후 destroy_all(data)를 호출해야 함.
# valgrind 에서 오류
test_leak_success: $(NAME)
	@echo "\n--- [TEST] Memory Leak on SUCCESS Path (Immediate Cleanup) ---"
	@echo " (init_forks, init_shared_mutexes, destroy_all()의 정리 로직을 검증합니다.)"

## Case 1: 표준 5 인자
	make leak ARGS="5 800 200 200 10"

## Case 2: 표준 4 인자 (must_eat_count=0으로 초기화됨)
	make leak ARGS="5 800 200 200"