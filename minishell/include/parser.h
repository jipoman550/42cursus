/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:05:12 by sisung            #+#    #+#             */
/*   Updated: 2026/02/04 20:33:18 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# include <stdio.h>
# include <fcntl.h>

# define SYNTAX_OK	0
# define E_TOKEN 	1
# define E_NEWLINE	2

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_REDIR_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

int		print_syntax_error(char *token_val);
int		check_syntax(t_token *tokens, char **err_token);

char	*safe_join(char *s1, char *s2);
char	*get_env_value(char *key, t_shell *sh);

void	split_argv_by_space(t_list **list, char *str);
void	expand_redirections(t_cmd *cmd, t_shell *sh);
void	remove_quotes_from_list(t_list *list);
char	**convert_list_to_argv(t_list *list);

int		run_expander(t_pipeline *pipeline, t_shell *sh);

int		is_valid_env(char c);

char	*expand_str(char *str, t_shell *sh);
void	update_quote_status(char c, char *quote);
int		is_expandable(char *str, int i, char quote);
int		is_tilde_exp(char *str, int i, char quote);

void	consume_heredoc_on_error(t_token *tokens, t_shell *sh);

int		ft_strcmp(const char *s1, const char *s2);
char	*get_tmp_filename(int i);
void	print_heredoc_warning(int start_line, char *limiter);
int		write_line_to_fd(int fd, char *line, int quoted, t_shell *sh);

int		process_heredocs(t_pipeline *pipeline, t_shell *sh);

int		ft_isspace(char c);
void	skip_spaces(char *line, int *i);
int		is_metachar(char c);

t_token	*lexer(char *line);

void	free_cmd_list_on_error(t_cmd *head);
t_redir	*new_redir(t_redir_type type, char *target);
void	redir_add_back(t_redir **head, t_redir *new);
int		count_args(t_token *token);

int		parse_to_cmd(t_token *tokens, t_pipeline **out);

char	*remove_quotes(char *str);

t_token	*new_token(t_token_type type, char *value);
void	token_add_back(t_token **head, t_token *new_node);
void	free_tokens(t_token *token);

#endif
