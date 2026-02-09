/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:51:47 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:39 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: 문자가 환경변수 이름으로 유효한지 확인 (알파벳, 숫자, 언더바).
** @param c 검사할 문자.
** @return 유효하면 1, 아니면 0.
*/
int	is_valid_env(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
** 함수 역할: 현재 문자에 따라 따옴표 상태(quote)를 업데이트.
** @param c 현재 문자.
** @param quote 현재 따옴표 상태 포인터.
*/
void	update_quote_status(char c, char *quote)
{
	if (*quote == 0 && (c == '\'' || c == '\"')) // 따옴표 시작
		*quote = c;
	else if (*quote != 0 && c == *quote) // 따옴표 종료
		*quote = 0;
}

/*
** 함수 역할: 현재 위치에서 환경변수 확장이 가능한지 확인.
** @param str 문자열.
** @param i 현재 인덱스.
** @param quote 현재 따옴표 상태.
** @return 확장 가능하면 1, 아니면 0.
*/
int	is_expandable(char *str, int i, char quote)
{
	if (str[i] == '$' && quote != '\'') // $ 기호이고 작은따옴표 안이 아닐 때
	{
		if (str[i + 1] && !ft_isspace(str[i + 1]) \
			&& str[i + 1] != '\"' && str[i + 1] != '\'') // 뒤에 유효한 문자가 오면
			return (1);
	}
	return (0);
}

/*
** 함수 역할: 현재 위치에서 틸드(~) 확장이 가능한지 확인.
** @param str 문자열.
** @param i 현재 인덱스.
** @param quote 현재 따옴표 상태.
** @return 확장 가능하면 1, 아니면 0.
*/
int	is_tilde_exp(char *str, int i, char quote)
{
	// 맨 앞이고, 따옴표 밖이며, 뒤에 /가 오거나 끝날 때
	return (str[i] == '~' && quote == 0 && i == 0
		&& (str[i + 1] == '\0' || str[i + 1] == '/'));
}
