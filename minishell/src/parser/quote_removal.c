/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:17:41 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:39 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: 문자열에서 가장 바깥쪽의 따옴표들을 제거.
** @param str 원본 문자열.
** @return 따옴표가 제거된 새 문자열.
*/
char	*remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	char	quote;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char)); // 메모리 할당
	quote = 0;
	i = 0;
	j = 0;
	while (str[i]) // 문자열 순회
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"')) // 따옴표 시작
			quote = str[i];
		else if (quote && str[i] == quote) // 따옴표 종료
			quote = 0;
		else
			new_str[j++] = str[i]; // 따옴표가 아니면 복사
		i++;
	}
	return (new_str);
}
