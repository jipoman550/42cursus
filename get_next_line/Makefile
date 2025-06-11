CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g -D BUFFER_SIZE=4

NAME	= test_get_next_line

SRCS	= main.c \
		  get_next_line.c \
		  get_next_line_utils.c

OBJS	= $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all