/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:05:12 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:49:24 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# include <stdio.h>
# include <fcntl.h>

# define SYNTAX_OK	0 // 구문 오류 없음
# define E_TOKEN 	1 // 토큰 오류
# define E_NEWLINE	2 // 개행 오류 (문장이 덜 끝남)

/*
** 토큰의 유형을 정의하는 열거형.
** T_WORD: 일반 단어 (명령어, 인자, 파일명 등).
** T_PIPE: 파이프 (|).
** T_REDIR_IN: 입력 리다이렉션 (<).
** T_REDIR_OUT: 출력 리다이렉션 (>).
** T_REDIR_APPEND: 이어쓰기 리다이렉션 (>>).
** T_REDIR_HEREDOC: 히어독 (<<).
*/
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_REDIR_HEREDOC
}	t_token_type;

/*
** 렉싱 단계에서 생성되는 토큰 구조체.
** type: 토큰 유형.
** value: 토큰 문자열 값.
** next: 다음 토큰.
*/
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* 구문 분석 및 에러 처리 */
int		print_syntax_error(char *token_val);
int		check_syntax(t_token *tokens, char **err_token);

/* 환경변수 및 문자열 유틸리티 */
char	*safe_join(char *s1, char *s2);
char	*get_env_value(char *key, t_shell *sh);

/* 확장(Expansion) 관련 함수들 */
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

/* 히어독(Heredoc) 처리 */
void	consume_heredoc_on_error(t_token *tokens, t_shell *sh);

int		ft_strcmp(const char *s1, const char *s2);
char	*get_tmp_filename(int i);
void	print_heredoc_warning(int start_line, char *limiter);
int		write_line_to_fd(int fd, char *line, int quoted, t_shell *sh);
int		process_heredocs(t_pipeline *pipeline, t_shell *sh);

/* 렉서(Lexer) 유틸리티 */
int		ft_isspace(char c);
void	skip_spaces(char *line, int *i);
int		is_metachar(char c);

/* 렉서 메인 */
t_token	*lexer(char *line);

/* 파서(Parser) 유틸리티 */
void	free_cmd_list_on_error(t_cmd *head);
t_redir	*new_redir(t_redir_type type, char *target);
void	redir_add_back(t_redir **head, t_redir *new);
int		count_args(t_token *token);

/* 파서 메인 */
int		parse_to_cmd(t_token *tokens, t_pipeline **out);

/* 따옴표 제거 */
char	*remove_quotes(char *str);

/* 토큰 리스트 관리 */
t_token	*new_token(t_token_type type, char *value);
void	token_add_back(t_token **head, t_token *new_node);
void	free_tokens(t_token *token);

#endif
