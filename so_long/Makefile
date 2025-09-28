# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 14:11:38 by sisung            #+#    #+#              #
#    Updated: 2025/09/25 17:31:49 by sisung           ###   ########.fr        #
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
	  			   map_validation.c \
				   path_validation.c \
				   path_validation_utils.c)

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

# ========================================================================= #
#                              TESTING SECTION                              #
# ========================================================================= #

# 테스트 디렉토리 정의
TEST_DIR = tests

# 테스트 파일 그룹
TEST_INITIAL_FAIL = $(wildcard $(TEST_DIR)/initial_fail/*.ber $(TEST_DIR)/initial_fail/*.txt)
TEST_PATH_FAIL = $(wildcard $(TEST_DIR)/path_fail/*.ber)
TEST_SUCCESS = $(wildcard $(TEST_DIR)/success_cases/*.ber)

# 테스트 타겟 정의
.PHONY: test test_initial_fail test_path_fail test_success clean_test
VALGRIND_LOG = valgrind_log.txt

# make test: Exit Code 검사와 Valgrind 검사를 모두 실행
test: all test_exit_codes test_valgrind
	@echo "\n========================================"
	@echo " ✅ ALL TESTS COMPLETED SUCCESSFULLY!    "
	@echo "========================================"

# --- 1. Exit Code 검사 타겟 (기존 *_fail 타겟을 통합) ---
test_exit_codes: test_initial_fail test_path_fail test_success

# 1-1. 초기 맵 유효성 검사 실패 테스트 (Exit Code 1 기대)
test_initial_fail:
	@echo "\n--- [Exit Code] INITIAL VALIDATION FAIL TESTS (Expecting Exit 1) ---"
	@for file in $(TEST_INITIAL_FAIL); do \
		echo -n "   - Testing $$file (Exit 1)... "; \
		./$(NAME) $$file > /dev/null 2>&1; \
		if [ $$? -ne 0 ]; then \
			echo "✅ PASSED"; \
		else \
			echo "❌ FAILED (No Error Exit)"; \
		fi; \
	done

# 1-2. 경로 유효성 검사 실패 테스트 (Exit Code 1 기대)
test_path_fail:
	@echo "\n--- [Exit Code] PATH VALIDATION FAIL TESTS (Expecting Exit 1) ---"
	@for file in $(TEST_PATH_FAIL); do \
		echo -n "   - Testing $$file (Exit 1)... "; \
		./$(NAME) $$file > /dev/null 2>&1; \
		if [ $$? -ne 0 ]; then \
			echo "✅ PASSED"; \
		else \
			echo "❌ FAILED (No Error Exit)"; \
		fi; \
	done

# 1-3. 성공 테스트 (Exit Code 0 기대)
test_success:
	@echo "\n--- [Exit Code] SUCCESS CASES TESTS (Expecting Exit 0) ---"
	@for file in $(TEST_SUCCESS); do \
		echo -n "   - Testing $$file (Exit 0)... "; \
		./$(NAME) $$file > /dev/null 2>&1; \
		if [ $$? -eq 0 ]; then \
			echo "✅ PASSED"; \
		else \
			echo "❌ FAILED (Error Exit)"; \
		fi; \
	done

# --- 2. Valgrind 메모리 누수 검사 타겟 (전체 대상) ---
test_valgrind:
	@echo "\n--- [Valgrind] STARTING MEMORY LEAK CHECK (All Test Cases) ---"
	@rm -f $(VALGRIND_LOG) # 기존 로그 파일 삭제
	@touch $(VALGRIND_LOG)

	@echo "Valgrind Logs will be saved to: $(VALGRIND_LOG)"

	# 모든 실패 테스트 케이스에 대해 Valgrind 실행
	@for file in $(TEST_INITIAL_FAIL) $(TEST_PATH_FAIL); do \
		echo -n "   - Checking FAIL CASE $$file... "; \
		valgrind --leak-check=full --show-leak-kinds=all \
				 --errors-for-leak-kinds=all --error-exitcode=100 \
				 ./$(NAME) $$file > /dev/null 2>> $(VALGRIND_LOG); \
		if [ $$? -ne 0 ]; then \
			echo "✅ PASSED (No Leaks)"; \
		else \
			echo "❌ FAILED (Leak or Error)"; \
		fi; \
	done

	# 모든 성공 테스트 케이스에 대해 Valgrind 실행
	@for file in $(TEST_SUCCESS); do \
		echo -n "   - Checking SUCCESS CASE $$file... "; \
		valgrind --leak-check=full --show-leak-kinds=all \
				 --errors-for-leak-kinds=all --error-exitcode=100 \
				 ./$(NAME) $$file > /dev/null 2>> $(VALGRIND_LOG); \
		if [ $$? -ne 0 ]; then \
			echo "❌ FAILED (Leak or Error)"; \
		else \
			echo "✅ PASSED (No Leaks)"; \
		fi; \
	done
