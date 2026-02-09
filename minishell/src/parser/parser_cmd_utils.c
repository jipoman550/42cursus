/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:02:21 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:38 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: 에러 발생 시 생성 중이던 명령어 리스트 메모리 해제.
** @param head 명령어 리스트 헤드.
*/
void	free_cmd_list_on_error(t_cmd *head)
{
	t_cmd	*temp;

	while (head) // 리스트 순회
	{
		temp = head;
		head = head->next;
		if (temp->argv)
			free_str_array(temp->argv); // 인자 배열 해제
		if (temp->redirs)
			free_redirs(temp->redirs); // 리다이렉션 리스트 해제
		free(temp); // 노드 해제
	}
}

/*
** 함수 역할: 새로운 리다이렉션 노드 생성 및 초기화.
** @param type 리다이렉션 타입.
** @param target 타겟 파일명 또는 종료자.
** @return 생성된 노드 포인터.
*/
t_redir	*new_redir(t_redir_type type, char *target)
{
	t_redir	*new;

	new = calloc(1, sizeof(t_redir)); // 메모리 할당
	if (!new)
		return (NULL);
	new->type = type; // 타입 설정
	new->target = target; // 타겟 설정
	new->next = NULL;
	return (new);
}

/*
** 함수 역할: 리다이렉션 리스트 끝에 새 노드 추가.
** @param head 리스트 헤드 포인터.
** @param new 추가할 노드.
*/
void	redir_add_back(t_redir **head, t_redir *new)
{
	t_redir	*curr;

	if (!new)
		return ;
	if (!*head) // 리스트가 비었으면
	{
		*head = new;
		return ;
	}
	curr = *head;
	while (curr->next) // 끝까지 이동
		curr = curr->next;
	curr->next = new; // 연결
}

/*
** 함수 역할: 파이프가 나오기 전까지 현재 명령어의 인자 개수 계산.
** @param token 현재 토큰 위치.
** @return 인자 개수.
*/
int	count_args(t_token *token)
{
	int	cnt;

	cnt = 0;
	while (token && token->type != T_PIPE) // 파이프 전까지
	{
		if (token->type >= T_REDIR_IN && token->type <= T_REDIR_HEREDOC) // 리다이렉션인 경우
		{
			if (token->next)
				token = token->next; // 타겟까지 건너뜀
		}
		else // 일반 단어인 경우
			cnt++; // 카운트 증가
		token = token->next;
	}
	return (cnt);
}
