/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:09:42 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:39 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: 환경변수($VAR)를 찾아 값을 확장하고 결과 문자열에 결합.
** @param str 원본 문자열.
** @param i 현재 인덱스 포인터.
** @param res 결과 문자열 포인터.
** @param sh 쉘 상태 구조체.
*/
static void	handle_env_var(char *str, int *i, char **res, t_shell *sh)
{
	int		start;
	char	*key;
	char	*val;

	(*i)++; // '$' 건너뛰기
	start = *i;
	if (str[*i] == '?') // $? 인 경우
	{
		(*i)++;
		key = ft_strdup("?");
	}
	else // 일반 변수인 경우
	{
		while (str[*i] && is_valid_env(str[*i])) // 유효한 환경변수 문자일 때까지
			(*i)++;
		key = ft_substr(str, start, *i - start); // 키 추출
	}
	val = get_env_value(key, sh); // 값 가져오기
	*res = safe_join(*res, val); // 결과에 결합
	free(key);
	free(val);
}

/*
** 함수 역할: 일반 문자열 부분을 결과에 결합.
** @param str 원본 문자열.
** @param start 시작 인덱스.
** @param end 끝 인덱스.
** @param res 결과 문자열 포인터.
*/
static void	append_normal_str(char *str, int start, int end, char **res)
{
	char	*chunk;

	if (start == end)
		return ;
	chunk = ft_substr(str, start, end - start); // 부분 문자열 추출
	*res = safe_join(*res, chunk); // 결합
	free(chunk);
}

/*
** 함수 역할: 틸드(~) 확장을 처리 ($HOME으로 치환).
** @param res 결과 문자열 포인터.
** @param i 현재 인덱스 포인터.
** @param start 시작 인덱스 포인터.
** @param sh 쉘 상태 구조체.
*/
static void	handle_tilde(char **res, int *i, int *start, t_shell *sh)
{
	char	*home;

	home = get_env_value("HOME", sh); // HOME 환경변수 가져오기
	if (!home)
		home = ft_strdup("");
	*res = safe_join(*res, home); // 결합
	free(home);
	*start = *i + 1; // 시작 위치 업데이트
}

/*
** 함수 역할: 문자열 내의 환경변수와 틸드를 확장.
** @param str 원본 문자열.
** @param sh 쉘 상태 구조체.
** @return 확장된 새 문자열.
*/
char	*expand_str(char *str, t_shell *sh)
{
	char	*res;
	char	quote;
	int		i;
	int		start;

	res = ft_strdup(""); // 결과 문자열 초기화
	quote = 0;
	i = -1;
	start = 0;
	while (str[++i]) // 문자열 순회
	{
		update_quote_status(str[i], &quote); // 따옴표 상태 업데이트
		if (is_tilde_exp(str, i, quote)) // 틸드 확장 조건 확인
			handle_tilde(&res, &i, &start, sh);
		else if (is_expandable(str, i, quote)) // 환경변수 확장 조건 확인
		{
			append_normal_str(str, start, i, &res); // 이전까지의 일반 문자열 추가
			handle_env_var(str, &i, &res, sh); // 변수 확장 수행
			start = i--; // 인덱스 조정 및 시작 위치 업데이트
		}
	}
	append_normal_str(str, start, i, &res); // 남은 문자열 추가
	return (res);
}
