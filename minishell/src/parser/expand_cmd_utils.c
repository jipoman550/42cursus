/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:34:13 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:38 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: 단어의 끝 인덱스를 찾음 (따옴표 처리 포함).
** @param str 문자열.
** @param i 시작 인덱스.
** @return 단어의 끝 인덱스.
*/
static int	get_word_end_idx(char *str, int i)
{
	char	quote;

	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"')) // 따옴표 시작
			quote = str[i];
		else if (quote && str[i] == quote) // 따옴표 종료
			quote = 0;
		if (!quote && ft_isspace(str[i])) // 따옴표 밖에서 공백을 만나면 끝
			break ;
		i++;
	}
	return (i);
}

/*
** 함수 역할: 문자열을 공백 기준으로 분리하여 리스트에 추가 (Word Splitting).
** @param list 결과 리스트.
** @param str 분리할 문자열.
*/
void	split_argv_by_space(t_list **list, char *str)
{
	int		i;
	int		end;
	char	*word;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i])) // 공백 건너뛰기
			i++;
		if (!str[i])
			break ;
		end = get_word_end_idx(str, i); // 단어 끝 찾기
		word = ft_substr(str, i, end - i); // 단어 추출
		if (word)
			ft_lstadd_back(list, ft_lstnew(word)); // 리스트에 추가
		i = end;
	}
}

/*
** 함수 역할: 리다이렉션 타겟에 대해 환경변수 확장 및 따옴표 제거 수행.
** @param cmd 명령어 구조체.
** @param sh 쉘 상태 구조체.
*/
void	expand_redirections(t_cmd *cmd, t_shell *sh)
{
	t_redir	*r;
	char	*expanded;
	char	*cleaned;

	r = cmd->redirs;
	while (r)
	{
		if (r->type != R_HEREDOC) // Heredoc이 아닌 경우만 확장
		{
			expanded = expand_str(r->target, sh); // 확장 수행
			free(r->target);
			cleaned = remove_quotes(expanded); // 따옴표 제거
			free(expanded);
			r->target = cleaned; // 결과 저장
		}
		r = r->next;
	}
}

/*
** 함수 역할: 리스트 내의 모든 문자열에서 따옴표 제거.
** @param list 문자열 리스트.
*/
void	remove_quotes_from_list(t_list *list)
{
	t_list	*curr;
	char	*cleaned;

	curr = list;
	while (curr)
	{
		cleaned = remove_quotes(curr->content); // 따옴표 제거
		free(curr->content); // 기존 문자열 해제
		curr->content = cleaned; // 새 문자열 연결
		curr = curr->next;
	}
}

/*
** 함수 역할: 연결 리스트를 문자열 배열(argv)로 변환.
** @param list 문자열 리스트.
** @return NULL로 끝나는 문자열 배열.
*/
char	**convert_list_to_argv(t_list *list)
{
	char	**new_argv;
	int		size;
	int		i;
	t_list	*curr;

	size = ft_lstsize(list); // 리스트 크기 계산
	new_argv = malloc(sizeof(char *) * (size + 1)); // 배열 할당
	if (!new_argv)
		return (NULL);
	curr = list;
	i = 0;
	while (curr)
	{
		new_argv[i++] = ft_strdup(curr->content); // 문자열 복제하여 저장
		curr = curr->next;
	}
	new_argv[i] = NULL; // NULL 종료
	return (new_argv);
}
