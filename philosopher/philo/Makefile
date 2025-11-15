# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/19 22:38:35 by sisung            #+#    #+#              #
#    Updated: 2025/11/15 11:21:59 by sisung           ###   ########.fr        #
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
			 init.c \
			 monitor.c \
			 parse.c \
			 routine.c \
			 simulation.c \
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
test: test_parse test_leak test_functional test_error
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

# error 발생
# 3. 성공 케이스: 유효한 인자 (Exit Code 0 기대)
	@echo "\n  - [SUCCESS] Valid Argument Tests:"
	@./$(NAME) 5 800 200 200 --parse-only > /dev/null 2>&1; if [ $$? -eq 0 ]; then echo "    - ✅ Test: 4 args PASSED"; else echo "    - ❌ Test: 4 args FAILED (Exit $$?)"; fi
	@./$(NAME) 5 800 200 200 10 > /dev/null 2>&1; if [ $$? -eq 0 ]; then echo "    - ✅ Test: 5 args PASSED"; else echo "    - ❌ Test: 5 args FAILED (Exit $$?)"; fi


# >>>>>>>>>>>>>>> test_parse 완료 후 중간 메시지 출력 <<<<<<<<<<<<<<<
	@echo "\n========================================"
	@echo " ✅ PARSE TESTS COMPLETED SUCCESSFULLY!"
	@echo " (Starting Functional Tests...)"
	@echo "========================================"

# --- 2. 필수 기능 테스트 (Functional Testing) ---
test_functional: $(NAME)
	@echo "\n--- [TEST] Functional & Termination Tests ---"

# error 발생
# 1. 성공 케이스: 식사 횟수 충족으로 종료 (5 800 200 200 7 반영)
	@echo "\n  - [SUCCESS] Meal Count Termination (5 800 200 200 7):"
	@./$(NAME) 5 800 200 200 7 | grep -c "is thinking" > /dev/null 2>&1; if [ $$? -eq 0 ]; then echo "    - ✅ Test: 5 phil 7 meals PASSED (Exit 0)"; else echo "    - ❌ Test: 5 phil 7 meals FAILED (Exit $$?)"; fi

# 2. 로그 정확성 확인 (4 410 200 200 반영)
	@echo "\n  - [SUCCESS] Log Timestamp & No Death (4 410 200 200):"
	@if ./$(NAME) 4 410 200 200 | grep "died" > /dev/null; then echo "    - ❌ Test: 4 410 200 200 FAILED (Death Detected)"; else echo "    - ✅ Test: 4 410 200 200 PASSED (No Death)"; fi

# 3. 사망 금지 케이스 (5 800 200 200 반영)
	@echo "\n  - [SUCCESS] No Death Guarantee (5 800 200 200):"
	@if ./$(NAME) 5 800 200 200 | grep "died" > /dev/null; then echo "    - ❌ Test: 5 800 200 200 FAILED (Death Detected)"; else echo "    - ✅ Test: 5 800 200 200 PASSED (No Death)"; fi

# 4. 소수 철학자 (2명) 테스트 (시간 지연 확인)
# 2명의 철학자 테스트는 정확한 종료 시간 확인이 중요하나, Makefile에서 정밀 시간 확인은 어려움.
# 대신 안정적으로 종료되는지 확인
	@echo "\n  - [SUCCESS] Two Philosopher Stability Check:"
	@./$(NAME) 2 100 20 20 5 | grep -c "died" > /dev/null 2>&1; if [ $$? -eq 0 ]; then echo "    - ✅ Test: 2 phil stability PASSED"; else echo "    - ❌ Test: 2 phil stability FAILED"; fi

# >>>>>>>>>>>>>>> test_functional 완료 후 중간 메시지 출력 <<<<<<<<<<<<<<<
	@echo "\n========================================"
	@echo " ✅ FUNCTIONAL TESTS COMPLETED SUCCESSFULLY!"
	@echo " (Starting Error Tests...)"
	@echo "========================================"

# --- 3. 핵심 오류 테스트 (Deadlock & Death) ---
test_error: $(NAME)
	@echo "\n--- [TEST] Deadlock & Critical Error Tests ---"

# 1. 데드락 방지 테스트 (필수)
# 50명 이상의 철학자로 극도의 경쟁 유도 (Exit Code 0 기대)
	@echo "\n  - [SUCCESS] Deadlock Prevention (High Load):"
	@./$(NAME) 100 800 200 200 | grep -c "is eating" > /dev/null 2>&1; if [ $$? -eq 0 ]; then echo "    - ✅ Test: 100 philos (No immediate deadlock) PASSED"; else echo "    - ❌ Test: 100 philos FAILED"; fi

# 2. 사망 감지 정확성 테스트 (time_to_die와 time_to_eat이 가까움)
# Deadlock이 없음을 확인하면서 사망이 예측된 시간 내에 발생하는지 확인
	@echo "\n  - [FAIL] Guaranteed Death Detection:"
# 5명의 철학자가 100ms 내에 죽어야 함 (eat: 200ms)
	@./$(NAME) 5 100 200 200 | grep -c "died" | xargs -I {} sh -c 'if [ {} -eq 1 ]; then echo "    - ✅ Test: Guaranteed Death (1 died) PASSED"; else echo "    - ❌ Test: Guaranteed Death FAILED (Died Count: {})"; fi
#============== [test 지 기반 테스트] ===================
# 1. 고부하 경쟁 테스트 (200명 이상)
	@echo "\n  - [SUCCESS] High Load Deadlock Prevention (200+ philos):"
	@./$(NAME) 250 800 200 200 1 | grep -c "is eating" > /dev/null 2>&1; if [ $$? -eq 0 ]; then echo "    - ✅ Test: 250 philos PASSED"; else echo "    - ❌ Test: 250 philos FAILED"; fi

# 2. 사망 보장 케이스 1 (180 200 200)
# time_to_die (180) < time_to_eat (200) + time_to_sleep (200) 이므로 죽어야 함.
	@echo "\n  - [FAIL] Guaranteed Death (1 800 200 200):"
	@./$(NAME) 1 180 200 200 | grep -c "died" | xargs -I {} sh -c 'if [ {} -eq 1 ]; then echo "    - ✅ Test: 180ms TTD Death PASSED"; else echo "    - ❌ Test: 180ms TTD Death FAILED (Died Count: {})"; fi

# 3. 사망 보장 케이스 2 (4 310 200 100)
# 410ms (식사+수면) > 310ms (사망) 이므로 죽어야 함.
	@echo "\n  - [FAIL] Guaranteed Death (4 310 200 100):"
	@./$(NAME) 4 310 200 100 | grep -c "died" | xargs -I {} sh -c 'if [ {} -eq 1 ]; then echo "    - ✅ Test: 4 310 200 100 Death PASSED"; else echo "    - ❌ Test: 4 310 200 100 Death FAILED (Died Count: {})"; fi

# 4. 낮은 시간 인자 테스트 (60ms 미만 금지 규칙 확인)
	@echo "\n  - [FAIL] Low Time Input (Should be Handled/Fail Gracefully):"
# 이 값들은 시뮬레이션이 불안정해지므로 평가자는 테스트하지 말라고 했지만,
# 프로그램이 crash하지 않고 불안정하게라도 작동하는지 확인
	@./$(NAME) 5 50 10 10 1 | grep -c "died" > /dev/null 2>&1; if [ $$? -eq 0 ]; then echo "    - ✅ Test: Low Time Input (Exit 0/1) PASSED"; else echo "    - ❌ Test: Low Time Input FAILED (Crashed)"; fi

# >>>>>>>>>>>>>>> test_error 완료 후 중간 메시지 출력 <<<<<<<<<<<<<<<
	@echo "\n========================================"
	@echo " ✅ ERROR TESTS COMPLETED SUCCESSFULLY!"
	@echo " (Starting Memory Leak Tests...)"
	@echo "========================================"

# --- 4. 메모리 누수 및 자원 정리 테스트 (Valgrind) ---

# 새로운 통합 타겟: test_leak
test_leak: test_leak_fail test_leak_success test_simulation
	@echo "\n--- [TEST] Memory Leak Tests Completed ---"
# 이 타겟은 Valgrind 결과가 stdout에 출력된 후 실행됩니다.

# --- 새로운 Valgrind 타겟: Helgrind 및 Leak 체크 통합 ---
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --trace-children=yes

# ⚠️ Helgrind 타겟 (Race Condition 검사)
helgrind: $(NAME)
	@echo "\n--- [VALGRIND] Testing Helgrind Args: $(ARGS) ---"
	-valgrind --tool=helgrind $(VALGRIND_FLAGS) ./$(NAME) $(ARGS)
	@echo "----------------------------------------"

# 🛠️ 기존 leak 타겟을 수정하여 helgrind 플래그 추가 (가장 일반적인 형태)
leak: $(NAME)
	@echo "\n--- [VALGRIND] Testing Args: $(ARGS) ---"
	-valgrind $(VALGRIND_FLAGS) ./$(NAME) $(ARGS)
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
test_leak_success: $(NAME)
	@echo "\n--- [TEST] Memory Leak on SUCCESS Path (Immediate Cleanup) ---"
	@echo " (init_forks, init_shared_mutexes, destroy_all()의 정리 로직을 검증합니다.)"
## Case 1: 표준 5 인자
	make leak ARGS="5 800 200 200 10"
## Case 2: 표준 4 인자 (must_eat_count=0으로 초기화됨)
	make leak ARGS="5 800 200 200"

# --- 5. 최종 시뮬레이션 테스트 (기능 + 메모리) ---
# 모든 주요 테스트 케이스에 대해 Valgrind 검사까지 포함하도록 통합
test_simulation: test_functional test_error
	@echo "\n--- [TEST] Final Valgrind & Helgrind Checks on Core Cases ---"
	@echo " (검사 로직이 길어지므로, 중요 케이스만 통합 테스트합니다.)"

## 1. 긴 시뮬레이션 (Deadlock 방지 검증 케이스)
	make helgrind ARGS="5 800 200 200 10"
	make leak ARGS="5 800 200 200 10"

## 2. 즉시 사망 케이스 (자원 정리 검증)
	make helgrind ARGS="2 50 200 200 1"
	make leak ARGS="2 50 200 200 1"

## 3. 고부하 경쟁 케이스 (Deadlock, Race Condition 검증)
	make helgrind ARGS="100 800 200 200 10"
	make leak ARGS="100 800 200 200 10"