# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/19 22:38:35 by sisung            #+#    #+#              #
#    Updated: 2026/01/19 11:03:24 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC         = cc
CFLAGS     = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread

NAME       = philo_bonus

# 소스 및 헤더 디렉토리
SRC_DIR    = .
OBJ_DIR	   = obj

# 소스 파일 목록 (현재 분리된 파일 기준)
SRC_FILES  = main_bonus.c \
			 cleanup_bonus.c \
			 init_bonus.c \
			 monitor_bonus.c \
			 parse_bonus.c \
			 routine_bonus.c \
			 simulation_bonus.c \
			 time_bonus.c \
			 utils_bonus.c

SRCS       = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# 오브젝트 파일 목록
OBJS       = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# obj 디렉토리 생성 및 오브젝트 컴파일
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c philo_bonus.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test test_parse test_functional test_error test_leak helgrind leak

# ========================================================================= #
#                                TEST SECTION                               #
# ========================================================================= #
TIMEOUT_VAL = 10s
TIMEOUT_CMD = timeout $(TIMEOUT_VAL)
SANITIZER = setarch $(uname -m) -R

# make test: 모든 테스트 실행
test: test_parse test_functional test_error test_leak
	@echo "\n========================================"
	@echo " ✅ ALL TESTS COMPLETED!"
	@echo "========================================"

# --- 1. 인자 파싱 및 유효성 검사 테스트 타겟 ---
test_parse: $(NAME)
	@echo "\n--- [TEST] Argument Parsing & Validation ---"
	@echo "\n  - [FAIL] Argument Count Tests:"
	@! ./$(NAME) 5 800 && echo "    - ✅ Test: Not enough args PASSED" || echo "    - ❌ Test: Not enough args FAILED"
	@! ./$(NAME) 5 800 200 200 5 500 && echo "    - ✅ Test: Too many args PASSED" || echo "    - ❌ Test: Too many args FAILED"
	@echo "\n  - [FAIL] Numeric Validation Tests:"
	@! ./$(NAME) 0 800 200 200 && echo "    - ✅ Test: Num_philo is zero PASSED" || echo "    - ❌ Test: Num_philo is zero FAILED"
	@! ./$(NAME) hello 800 200 200 && echo "    - ✅ Test: Non-numeric arg PASSED" || echo "    - ❌ Test: Non-numeric arg FAILED"
	@echo "\n========================================"
	@echo " ✅ PARSE TESTS COMPLETED!"
	@echo "========================================"

# --- 2. 필수 기능 테스트 (Functional Testing) ---
test_functional: $(NAME)
	@echo "\n--- [TEST] Functional & Termination Tests ---"
	@echo "\n  - [SUCCESS] Meal Count Termination (5 800 200 200 7):"
	@if $(SANITIZER) ./$(NAME) 5 800 200 200 7; then echo "    - ✅ Test: 5 phil 7 meals PASSED"; else echo "    - ❌ Test: 5 phil 7 meals FAILED"; fi
	@echo "\n  - [SUCCESS] No Death (4 410 200 200):"
	@if ! $(SANITIZER) $(TIMEOUT_CMD) ./$(NAME) 4 410 200 200 | grep -q "died"; then echo "    - ✅ Test: 4 410 200 200 PASSED"; else echo "    - ❌ Test: 4 410 200 200 FAILED (Death Detected)"; fi
	@echo "\n  - [SUCCESS] No Death (5 800 200 200):"
	@if ! $(SANITIZER) $(TIMEOUT_CMD) ./$(NAME) 5 800 200 200 | grep -q "died"; then echo "    - ✅ Test: 5 800 200 200 PASSED"; else echo "    - ❌ Test: 5 800 200 200 FAILED (Death Detected)"; fi
	@echo "\n  - [SUCCESS] Two Philosopher Stability Check (2 100 20 20 5):"
	@if $(SANITIZER) ./$(NAME) 2 100 20 20 5; then echo "    - ✅ Test: 2 100 20 20 5 PASSED"; else echo "    - ❌ Test: 2 100 20 20 5 FAILED (Death Detected)"; fi
	@echo "\n========================================"
	@echo " ✅ FUNCTIONAL TESTS COMPLETED!"
	@echo "========================================"

# --- 3. 핵심 오류 테스트 (Deadlock & Death) ---
test_error: $(NAME)
	@echo "\n--- [TEST] Deadlock & Critical Error Tests ---"
	@echo "\n  - [SUCCESS] Deadlock Prevention (200 philos, 1 meal):"
	@if $(SANITIZER) ./$(NAME) 200 800 200 200 1; then echo "    - ✅ Test: 200 philos PASSED"; else echo "    - ❌ Test: 200 philos FAILED"; fi
	@echo "\n  - [FAIL] Guaranteed Death Detection (5 100 200 200):"
	@if $(SANITIZER) ./$(NAME) 5 100 200 200 | grep -q "died"; then echo "    - ✅ Test: Guaranteed Death PASSED"; else echo "    - ❌ Test: Guaranteed Death FAILED (No death detected)"; fi
	@echo "\n  - [FAIL] Guaranteed Death (1 philo):"
	@if $(SANITIZER) ./$(NAME) 1 800 200 200 | grep -q "died"; then echo "    - ✅ Test: 1 philo death PASSED"; else echo "    - ❌ Test: 1 philo death FAILED (No death detected)"; fi
	@echo "\n  - [FAIL] Guaranteed Death (4 310 200 100):"
	@if $(SANITIZER) ./$(NAME) 4 310 200 100 | grep -q "died"; then echo "    - ✅ Test: 4 310 200 100 Death PASSED"; else echo "    - ❌ Test: 4 310 200 100 Death FAILED (No death detected)"; fi
	@echo "\n  - [FAIL] Low Time Input (Should be Handled/Fail Gracefully) (5 50 10 10 1):"
# 마지막 테스트는 안해도 되긴함. 조건에 안 맞는데 해보는 거임. 확실히 시간이 촉박하니 is_dead check가 늦네.
	@if $(SANITIZER) ./$(NAME) 5 50 10 10 1; then echo "    - ✅ Test: 5 50 10 10 1 Death PASSED"; else echo "    - ❌ Test: 5 50 10 10 1 Death FAILED (No death detected)"; fi
	@echo "\n========================================"
	@echo " ✅ ERROR TESTS COMPLETED!"
	@echo "========================================"

# --- 4. 메모리 누수 및 자원 정리 테스트 (Valgrind) ---
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --trace-children=yes

test_leak: $(NAME)
	@echo "\n--- [TEST] Memory Leak & Race Condition Tests ---"
	@echo " (All Valgrind/Helgrind tests should show no errors or leaks)"

	@echo "\n  - [LEAK] Normal execution (4 410 200 200 5):"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME) 4 410 200 200 5 > valgrind.log 2>&1 || true; \
	cat valgrind.log; \
	if grep -q "ERROR SUMMARY: 0 errors" valgrind.log; then echo "    - ✅ PASSED"; else echo "    - ❌ FAILED (Check output)"; fi

	@echo "\n  - [LEAK] Guaranteed death (4 310 200 100):"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME) 4 310 200 100 > valgrind.log 2>&1 || true; \
	cat valgrind.log; \
	if grep -q "ERROR SUMMARY: 0 errors" valgrind.log; then echo "    - ✅ PASSED"; else echo "    - ❌ FAILED (Check output)"; fi

	@echo "\n  - [HELGRIND] Race condition check (5 800 200 200 7):"
	@valgrind --tool=helgrind ./$(NAME) 5 800 200 200 7 > helgrind.log 2>&1 || true; \
	cat helgrind.log; \
	if grep -q "ERROR SUMMARY: 0 errors" helgrind.log; then echo "    - ✅ PASSED"; else echo "    - ❌ FAILED (Check output)"; fi

	@rm -f valgrind.log helgrind.log
	@echo "\n========================================"
	@echo " ✅ MEMORY & RACE CONDITION TESTS COMPLETED!"
	@echo "========================================"

# --- Valgrind Helper Targets ---
helgrind:
	@echo "\n--- [VALGRIND] Testing Helgrind Args: $(ARGS) ---"
	valgrind --tool=helgrind $(VALGRIND_FLAGS) ./$(NAME) $(ARGS)

leak:
	@echo "\n--- [VALGRIND] Testing Leak Args: $(ARGS) ---"
	valgrind $(VALGRIND_FLAGS) ./$(NAME) $(ARGS)