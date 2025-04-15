# 컴파일러 및 플래그
CC = cc
CFLAGS = -Wall -Wextra -Werror

# 프로젝트 이름
NAME = libft.a

# 소스 파일 - 필수 부분(파트 1과 파트 2 통합)
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
      ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
      ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
      ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
      ft_atoi.c ft_calloc.c ft_strdup.c \
      ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
      ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
      ft_putendl_fd.c ft_putnbr_fd.c

# 보너스 소스 파일
BONUS_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
            ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
            ft_lstmap_bonus.c

# 오브젝트 파일
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# 기본 타겟: 전체 필수 라이브러리 컴파일
all: $(NAME)

# 오브젝트 파일로부터 라이브러리 생성
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

# 보너스 규칙 - 라이브러리에 보너스 함수 추가
bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

# 오브젝트 파일을 위한 패턴 규칙
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 오브젝트 파일 정리
clean:
	rm -f $(OBJ) $(BONUS_OBJ)

# 모든 것 제거
fclean: clean
	rm -f $(NAME)

# 모든 것 재빌드
re: fclean all

# 이 규칙들은 파일에 해당하지 않음
.PHONY: all clean fclean re bonus