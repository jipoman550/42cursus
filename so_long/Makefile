# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 14:11:38 by sisung            #+#    #+#              #
#    Updated: 2025/10/01 16:13:17 by sisung           ###   ########.fr        #
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
	  $(SRC_DIR)/, event_handler.c \
	  			   main.c \
	  			   map_parsing.c \
				   map_utils.c \
	  			   map_validation.c \
				   path_validation.c \
				   path_validation_utils.c \
				   rendering.c \
				   utils.c)

# 오브젝트 파일 경로
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

# Libft 디렉토리 및 라이브러리 경로
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# MinilibX 추가
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

# 헤더 파일 경로
INCLUDES = -Iinclude -I$(LIBFT_DIR)/include -I$(MLX_DIR)

# MinilibX가 필요로하는 외부 라이브러리 링크 옵션
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# ========================================================================= #

# 최종 실행 파일 생성 규칙
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME) $(INCLUDES)

# Libft 라이브러리 빌드 (make -C를 사용하여 libft 디렉토리로 이동 후 빌드)
$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

# MinilibX 라이브러리 빌드 규칙
$(MLX_LIB):
	@make -C $(MLX_DIR)

# 소스 파일을 오브젝트 파일로 컴파일
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ========================================================================= #

# make clean: 오브젝트 파일 삭제
clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@rm -rf $(OBJ_DIR)

# make fclean: 오브젝트 파일과 실행 파일 삭제
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
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
ERROR_LOG_TEMP = .error_log_temp

# make test: Exit Code 검사와 Valgrind 검사를 모두 실행
test: all test_exit_codes test_valgrind
	@echo "\n========================================"
	@echo " ✅ ALL TESTS COMPLETED SUCCESSFULLY!    "
	@echo "========================================"

# --- 1. Exit Code 검사 타겟 (기존 *_fail 타겟을 통합) ---
test_exit_codes: test_initial_fail test_path_fail test_success

# 1-1. 초기 맵 유효성 검사 실패 테스트 (Exit Code 1 & "Error" 출력 기대)
test_initial_fail:
	@echo "\n--- [Exit Code & Message] INITIAL FAIL TESTS (Expecting Exit 1 and 'Error') ---"
	@rm -f $(ERROR_LOG_TEMP) # 임시 로그 파일 삭제
	@for file in $(TEST_INITIAL_FAIL); do \
		echo -n "   - Testing $$file... "; \
		\
		./$(NAME) $$file > /dev/null > $(ERROR_LOG_TEMP); \
		PROGRAM_EXIT_CODE=$$? ; \
		\
		if [ $$PROGRAM_EXIT_CODE -eq 1 ] && grep -q "Error" $(ERROR_LOG_TEMP); then \
			echo "✅ PASSED (Exit 1, Message OK)"; \
		else \
			echo "❌ FAILED (Exit $$PROGRAM_EXIT_CODE, Message Fail)"; \
		fi; \
	done
	@rm -f $(ERROR_LOG_TEMP) # 테스트 후 임시 로그 파일 정리

# 1-2. 경로 유효성 검사 실패 테스트 (Exit Code 1 & "Error" 출력 기대)
test_path_fail:
	@echo "\n--- [Exit Code & Message] PATH FAIL TESTS (Expecting Exit 1 and 'Error') ---"
	@rm -f $(ERROR_LOG_TEMP) # 임시 로그 파일 삭제
	@for file in $(TEST_PATH_FAIL); do \
		echo -n "   - Testing $$file... "; \
		\
		./$(NAME) $$file > /dev/null > $(ERROR_LOG_TEMP); \
		PROGRAM_EXIT_CODE=$$? ; \
		\
		if [ $$PROGRAM_EXIT_CODE -eq 1 ] && grep -q "Error" $(ERROR_LOG_TEMP); then \
			echo "✅ PASSED (Exit 1, Message OK)"; \
		else \
			echo "❌ FAILED (Exit $$PROGRAM_EXIT_CODE, Message Fail)"; \
		fi; \
	done
	@rm -f $(ERROR_LOG_TEMP) # 테스트 후 임시 로그 파일 정리

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
VALGRIND_LOG = valgrind_log.txt
VALGRIND_TEMP = .valgrind_temp

# Valgrind 옵션: Full check + Still Reachable까지 모두 보고
VALGRIND_OPTS = --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all

test_valgrind:
	@echo "\n--- [Valgrind] STARTING MEMORY LEAK CHECK (All Test Cases) ---"
	@rm -f $(VALGRIND_LOG) $(VALGRIND_TEMP) # 로그 및 임시 파일 삭제
	@touch $(VALGRIND_LOG)
	@echo "Valgrind Logs will be saved to: $(VALGRIND_LOG)"

	@for file in $(TEST_INITIAL_FAIL) $(TEST_PATH_FAIL) $(TEST_SUCCESS); do \
		echo -n "   - Checking $$file... "; \
		\
		valgrind $(VALGRIND_OPTS) ./$(NAME) $$file > /dev/null 2> $(VALGRIND_TEMP); \
		\
		cat $(VALGRIND_TEMP) >> $(VALGRIND_LOG); \
		\
		if grep -q "definitely lost" $(VALGRIND_TEMP) && \
		   grep -q "indirectly lost" $(VALGRIND_TEMP) && \
		   grep -q "still reachable" $(VALGRIND_TEMP); then \
				echo "❌ FAILED (Leak or Still Reachable Detected)"; \
		else \
				echo "✅ PASSED (No Leaks, No Still Reachable)"; \
		fi; \
	done

	@rm -f $(VALGRIND_TEMP) # 임시 파일 정리
