/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:19:17 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:37 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: 구문 오류 메시지를 출력하고 에러 코드를 반환.
** @param token_val 오류가 발생한 토큰의 값.
** @return 항상 258 (구문 오류 코드) 반환.
*/
int	print_syntax_error(char *token_val)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2); // 에러 메시지 앞부분 출력
	ft_putstr_fd(token_val, 2); // 문제의 토큰 출력
	ft_putstr_fd("'\n", 2); // 에러 메시지 뒷부분 및 개행 출력
	return (258); // 에러 코드 반환
}

/*
** 함수 역할: 파이프(|) 관련 구문 오류 검사.
** @param token 현재 검사 중인 토큰.
** @param err_token 오류 발생 시 해당 토큰 값을 저장할 포인터.
** @return 오류 없으면 SYNTAX_OK, 있으면 에러 타입(E_NEWLINE, E_TOKEN).
*/
static int	check_pipe_syntax(t_token *token, char **err_token)
{
	if (token->type != T_PIPE) // 파이프가 아니면 통과
		return (SYNTAX_OK);
	if (!token->next) // 파이프 뒤에 아무것도 없으면 (문장 끝)
	{
		*err_token = "newline"; // 에러 토큰을 newline으로 설정
		return (E_NEWLINE); // 개행 에러 반환
	}
	if (token->next->type == T_PIPE) // 파이프 바로 뒤에 또 파이프가 오면 (||)
	{
		*err_token = token->next->value; // 다음 파이프 값을 에러 토큰으로 설정
		return (E_TOKEN); // 토큰 에러 반환
	}
	return (SYNTAX_OK); // 문제 없음
}

/*
** 함수 역할: 리다이렉션(<, >, <<, >>) 관련 구문 오류 검사.
** @param token 현재 검사 중인 토큰.
** @param err_token 오류 발생 시 해당 토큰 값을 저장할 포인터.
** @return 오류 없으면 SYNTAX_OK, 있으면 에러 타입.
*/
static int	check_redir_syntax(t_token *token, char **err_token)
{
	if (token->type < T_REDIR_IN || token->type > T_REDIR_HEREDOC) // 리다이렉션 토큰이 아니면 통과
		return (SYNTAX_OK);
	if (!token->next) // 리다이렉션 뒤에 아무것도 없으면
	{
		*err_token = "newline"; // 에러 토큰 설정
		return (E_NEWLINE); // 개행 에러 반환
	}
	if (token->next->type != T_WORD) // 리다이렉션 뒤에 일반 단어(파일명/종료자)가 오지 않으면
	{
		*err_token = token->next->value; // 잘못된 토큰 설정
		return (E_TOKEN); // 토큰 에러 반환
	}
	return (SYNTAX_OK); // 문제 없음
}

/*
** 함수 역할: 전체 토큰 리스트를 순회하며 구문 오류 검사.
** @param tokens 검사할 토큰 리스트 헤드.
** @param err_token 오류 발생 시 저장할 토큰 값 포인터.
** @return 오류 상태 코드 (SYNTAX_OK 또는 에러 코드).
*/
int	check_syntax(t_token *tokens, char **err_token)
{
	int	status;

	*err_token = NULL; // 에러 토큰 초기화
	if (!tokens) // 토큰이 없으면(빈 줄) OK
		return (SYNTAX_OK);
	if (tokens->type == T_PIPE) // 첫 토큰이 파이프면 에러 (| ls 등)
	{
		*err_token = tokens->value; // 에러 토큰 설정
		return (E_TOKEN); // 에러 반환
	}
	while (tokens) // 리스트 순회
	{
		status = check_pipe_syntax(tokens, err_token); // 파이프 문법 검사
		if (status != SYNTAX_OK)
			return (status); // 에러 발생 시 즉시 반환
		status = check_redir_syntax(tokens, err_token); // 리다이렉션 문법 검사
		if (status != SYNTAX_OK)
			return (status); // 에러 발생 시 즉시 반환
		tokens = tokens->next; // 다음 토큰으로 이동
	}
	return (SYNTAX_OK); // 모든 검사 통과
}
