/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 08:17:31 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:10:06 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: 리다이렉션 기호(<, >)를 감지하여 토큰 리스트에 추가. <<, >> 처리 포함.
** @param line 입력 문자열.
** @param i 현재 인덱스 포인터 (업데이트됨).
** @param c 현재 문자 (< 또는 >).
** @param head 토큰 리스트 헤드 포인터.
*/
static void	add_redir_token(char *line, int *i, char c, t_token **head)
{
	if (line[*i + 1] == c) // 다음 문자도 동일하면 (<< 또는 >>)
	{
		if (c == '<')
			token_add_back(head, new_token(T_REDIR_HEREDOC, ft_strdup("<<"))); // Heredoc 토큰 추가
		else
			token_add_back(head, new_token(T_REDIR_APPEND, ft_strdup(">>"))); // Append 토큰 추가
		(*i) += 2; // 인덱스 2 증가
	}
	else // 단일 문자 (< 또는 >)
	{
		if (c == '<')
			token_add_back(head, new_token(T_REDIR_IN, ft_strdup("<"))); // Input Redir 토큰 추가
		else
			token_add_back(head, new_token(T_REDIR_OUT, ft_strdup(">"))); // Output Redir 토큰 추가
		(*i)++; // 인덱스 1 증가
	}
}

/*
** 함수 역할: 현재 문자가 연산자(|, <, >)인지 확인하고 토큰화.
** @param line 입력 문자열.
** @param i 현재 인덱스 포인터.
** @param head 토큰 리스트 헤드.
** @return 연산자 처리 시 1, 아니면 0.
*/
static int	tokenize_operator(char *line, int *i, t_token **head)
{
	char	c;

	c = line[*i];
	if (c == '|') // 파이프인 경우
	{
		token_add_back(head, new_token(T_PIPE, ft_strdup("|"))); // 파이프 토큰 추가
		(*i)++; // 인덱스 증가
		return (1); // 처리됨 반환
	}
	else if (c == '<' || c == '>') // 리다이렉션 문자인 경우
	{
		add_redir_token(line, i, c, head); // 리다이렉션 토큰 처리 함수 호출
		return (1); // 처리됨 반환
	}
	return (0); // 연산자가 아님
}

/*
** 함수 역할: 단어(Word)의 끝 인덱스를 찾음. 따옴표 내부의 메타 문자는 무시. 닫히지 않은 따옴표 검사.
** @param line 입력 문자열.
** @param i 검색 시작 인덱스.
** @param end_idx 결과 끝 인덱스를 저장할 포인터.
** @return 성공 시 0, 에러(닫히지 않은 따옴표) 시 -1.
*/
static int	scan_word_end(char *line, int i, int *end_idx)
{
	char	quote;

	quote = 0;
	while (line[i]) // 문자열 끝까지 반복
	{
		if (!quote && (line[i] == '\'' || line[i] == '\"')) // 따옴표 시작 감지
			quote = line[i];
		else if (quote && line[i] == quote) // 따옴표 닫힘 감지
			quote = 0;
		if (!quote && is_metachar(line[i])) // 따옴표 밖에서 메타 문자(공백, |, <, >)를 만나면 단어 끝
			break ;
		i++;
	}
	*end_idx = i; // 끝 인덱스 저장
	if (quote != 0) // 반복이 끝났는데 따옴표가 닫히지 않은 경우
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2); // 에러 메시지 출력
		return (-1); // 에러 반환
	}
	return (0); // 성공
}

/*
** 함수 역할: 일반 단어 토큰을 생성하여 리스트에 추가.
** @param line 입력 문자열.
** @param i 현재 인덱스 포인터.
** @param head 토큰 리스트 헤드.
** @return 성공 시 0, 실패 시 -1.
*/
static int	tokenize_word(char *line, int *i, t_token **head)
{
	int		start;
	int		end;
	char	*word;

	start = *i; // 단어 시작 위치 저장
	if (scan_word_end(line, *i, &end) == -1) // 단어의 끝 위치 탐색 (따옴표 처리 포함)
		return (-1); // 에러 발생 시 리턴
	word = ft_substr(line, start, end - start); // 시작부터 끝까지 부분 문자열 생성
	if (!word)
		return (-1); // 메모리 할당 실패 시
	token_add_back(head, new_token(T_WORD, word)); // WORD 토큰 생성 및 리스트 추가
	*i = end; // 현재 인덱스를 단어 끝으로 업데이트
	return (0);
}

/*
** 함수 역할: 입력 문자열을 순회하며 토큰 리스트 생성 (Lexical Analysis).
** @param line 사용자 입력 문자열.
** @return 생성된 토큰 리스트의 헤드 (실패 시 NULL).
*/
t_token	*lexer(char *line)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (line[i]) // 문자열 끝까지 반복
	{
		skip_spaces(line, &i); // 공백 건너뛰기
		if (!line[i]) // 문자열 끝이면 종료
			break ;
		if (tokenize_operator(line, &i, &head)) // 연산자(파이프, 리다이렉션) 토큰화 시도
			continue ; // 연산자 처리했으면 다음 루프로
		if (tokenize_word(line, &i, &head) == -1) // 일반 단어 토큰화 시도
		{
			free_tokens(head); // 실패 시 생성된 토큰 모두 해제
			return (NULL); // NULL 반환
		}
	}
	return (head); // 생성된 토큰 리스트 반환
}
