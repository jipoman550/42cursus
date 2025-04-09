
# Libft 프로젝트를 위한 Makefile

# 컴파일러 및 플래그
CC = cc
CFLAGS = -Wall -Wextra -Werror

# 프로젝트 이름
NAME = libft.a

# Part 1 소스 파일 (Libc 함수들)
SRC_P1 = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
         ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
         ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
         ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
         ft_atoi.c ft_calloc.c ft_strdup.c

# Part 2 소스 파일 (추가 함수들)
SRC_P2 = ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
         ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
         ft_putendl_fd.c ft_putnbr_fd.c

# 보너스 소스 파일
SRC_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
           ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
           ft_lstmap.c

# 오브젝트 파일
OBJ_P1 = $(SRC_P1:.c=.o)
OBJ_P2 = $(SRC_P2:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

# 기본 타겟: Part 1만 컴파일
all: $(NAME)

# Part 1 함수로 라이브러리 생성하는 규칙
$(NAME): $(OBJ_P1)
	ar rcs $(NAME) $(OBJ_P1)
	@echo "Part 1 함수로 라이브러리 생성 완료"

# Part 2 함수를 라이브러리에 추가하는 규칙
part2: $(OBJ_P1) $(OBJ_P2)
	ar rcs $(NAME) $(OBJ_P1) $(OBJ_P2)
	@echo "Part 2 함수로 라이브러리 업데이트 완료"

# 보너스 규칙: 보너스 함수를 라이브러리에 추가
bonus: $(OBJ_P1) $(OBJ_P2) $(OBJ_BONUS)
	ar rcs $(NAME) $(OBJ_P1) $(OBJ_P2) $(OBJ_BONUS)
	@echo "보너스 함수로 라이브러리 업데이트 완료"

# 소스 파일을 오브젝트 파일로 컴파일하는 규칙
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 오브젝트 파일 정리
clean:
	rm -f $(OBJ_P1) $(OBJ_P2) $(OBJ_BONUS)
	@echo "오브젝트 파일 제거 완료"

# 모든 것 정리
fclean: clean
	rm -f $(NAME)
	@echo "라이브러리 제거 완료"

# 모든 것 재빌드
re: fclean all

# 이 규칙들은 파일에 해당하지 않음
.PHONY: all clean fclean re part2 bonus