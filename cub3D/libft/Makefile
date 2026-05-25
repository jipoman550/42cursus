# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sisung <sisung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 11:05:14 by sisung            #+#    #+#              #
#    Updated: 2025/06/03 10:13:13 by sisung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

NAME = libft.a

# ft_printf 과제 디렉토리 이름
PRINTF_LIB_DIR = ftp

# ft_printf 과제에서 만들 라이브러리 이름
PRINTF_LIB = $(PRINTF_LIB_DIR)/libftprintf.a

SRC = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c

BONUS_SRC = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(PRINTF_LIB) $(NAME)

# ftp 내의 libftprintf.a 를 생성함.
# ftp 디렉으로 이동하여 make 실행
$(PRINTF_LIB):
	@make -C $(PRINTF_LIB_DIR)

# 최종 libft.a를 생성함.
$(NAME): $(PRINTF_LIB) $(OBJ)
	cp $(PRINTF_LIB) $(NAME)
	ar rcs $(NAME) $(OBJ)

.bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
	@touch .bonus

bonus: .bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	rm -f .bonus
	@make -C $(PRINTF_LIB_DIR) fclean

fclean: clean
	rm -f $(NAME)
	@make -C $(PRINTF_LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus