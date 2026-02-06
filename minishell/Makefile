# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 17:13:40 by sisung            #+#    #+#              #
#    Updated: 2026/02/04 13:58:29 by hama             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------------------------------------------------------
# Variables
# ------------------------------------------------------------------------------
NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR 	= include
LIBFT_DIR 	= libft

# Libraries
LIBFT		= $(LIBFT_DIR)/libft.a
LIBS		= -L$(LIBFT_DIR) -lft -lreadline

# Includes (-I switch)
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

# Source Files
SRCS_FILES	= main.c \
			  free_utils.c \
			  signals.c \
			  parser/check_syntax.c \
			  parser/env_utils.c \
			  parser/expand_cmd_utils.c \
			  parser/expand_cmd.c \
			  parser/expand_utils.c \
			  parser/expand.c \
			  parser/heredoc_on_error.c \
			  parser/heredoc_utils.c \
			  parser/heredoc.c \
			  parser/lexer_utils.c \
			  parser/lexer.c \
			  parser/parser_cmd_utils.c \
			  parser/parser_cmd.c \
			  parser/parser.c \
			  parser/quote_removal.c \
			  parser/token_list_utils.c \
			  exec/exe_pipeline.c \
			  exec/exe_single_cmd.c \
			  exec/exe_utils1.c \
			  exec/exe_utils2.c \
			  exec/exe_builtin.c \
			  exec/exe_redir.c \
			  exec/exe_external.c \
			  exec/is_builtin.c \
			  exec/ft_builtin/ft_cd.c \
			  exec/ft_builtin/ft_echo.c \
			  exec/ft_builtin/ft_env.c \
			  exec/ft_builtin/ft_exit.c \
			  exec/ft_builtin/ft_export.c \
			  exec/ft_builtin/ft_export_print.c \
			  exec/ft_builtin/ft_pwd.c \
			  exec/ft_builtin/ft_unset.c \
			  exec/ft_builtin/env_utils/env_copy.c \
			  exec/ft_builtin/env_utils/env_set_unset.c \
			  exec/ft_builtin/env_utils/env_utils.c \
			  exec/ft_builtin/env_utils/env_valid.c \

SRCS		= $(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS		= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# ------------------------------------------------------------------------------
# Rules
# ------------------------------------------------------------------------------

# Main Rule
all: $(NAME)

# Link Rule (Executable)
# If there isn't libft, libft compile first, and then link minishell
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

# Compile Rule (Object file)
# If there isn't obj file, make it and then make .o files following src structure
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Libft Compile Rule
$(LIBFT):
	@make bonus -C $(LIBFT_DIR)

#Clean Rules
clean:
	@make -C $(LIBFT_DIR) clean
	$(RM) $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
