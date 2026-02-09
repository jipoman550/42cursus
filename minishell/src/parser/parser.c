/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:04:15 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 16:54:26 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: 구문 오류(Syntax Error) 발생 시 처리. 에러 메시지 출력 및 상태 설정.
** @param tokens 파싱 중이던 토큰 리스트 (해제용).
** @param type 오류 유형 (E_TOKEN, E_NEWLINE 등).
** @param err 오류를 유발한 토큰 문자열.
** @param sh 쉘 상태 구조체 (종료 상태 설정용).
** @return 항상 258 (구문 오류 종료 코드) 반환.
*/
static int	handle_syntax_error(t_token *tokens, int type, \
								char *err, t_shell *sh)
{
	if (type == E_TOKEN) // 잘못된 토큰으로 인한 에러인 경우
		print_syntax_error(err); // 에러 메시지 출력
	consume_heredoc_on_error(tokens, sh); // 에러가 있어도 이미 입력된 Heredoc은 소모해야 함
	if (g_exit_code != SIGINT && type == E_NEWLINE) // SIGINT가 아니고 줄바꿈 에러인 경우
		print_syntax_error(err); // 에러 메시지 출력
	free_tokens(tokens); // 토큰 리스트 메모리 해제
	sh->last_status = 258 % 256; // 종료 상태를 258로 설정 (실제로는 2)
	return (258); // 에러 코드 반환
}

/*
** 함수 역할: 입력 라인을 파싱하여 실행 가능한 파이프라인 구조체로 변환.
** @param line 사용자가 입력한 원본 문자열.
** @param out 결과 파이프라인 구조체를 저장할 포인터.
** @param sh 쉘 상태 구조체.
** @return 성공 시 0, 실패 시 1 또는 -1.
*/
int	parse_line(const char *line, t_pipeline **out, t_shell *sh)
{
	t_token	*tokens;
	char	*err_token;
	int		syntax_type;

	tokens = lexer((char *)line); // 1. 렉서: 문자열을 토큰 리스트로 분리
	if (!tokens) // 토큰 생성 실패 시 (빈 입력 등)
		return (-1);
	err_token = NULL;
	syntax_type = check_syntax(tokens, &err_token); // 2. 구문 검사: 문법 오류 확인
	if (syntax_type != SYNTAX_OK) // 오류 발견 시
		return (handle_syntax_error(tokens, syntax_type, err_token, sh)); // 에러 처리 핸들러 호출
	if (parse_to_cmd(tokens, out) == -1) // 3. 파서: 토큰을 명령어 구조체(AST)로 변환
	{
		free_tokens(tokens); // 실패 시 토큰 해제
		ft_putstr_fd("minishell: memory allocation error\n", 2); // 메모리 에러 출력
		return (1);
	}
	free_tokens(tokens); // 변환 완료 후 토큰 리스트는 더 이상 필요 없으므로 해제
	// 4. 후처리: Heredoc 처리 및 환경변수 확장 수행
	if (process_heredocs(*out, sh) || run_expander(*out, sh))
	{
		free_pipeline(*out); // 실패 시 파이프라인 해제
		*out = NULL;
		return (1);
	}
	return (0);
}
