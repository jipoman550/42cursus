/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 08:39:32 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:22:48 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: 새로운 토큰 노드를 생성하고 초기화.
** @param type 토큰의 유형 (T_WORD, T_PIPE 등).
** @param value 토큰이 가지는 문자열 값.
** @return 생성된 토큰 구조체 포인터 (실패 시 NULL).
*/
t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token)); // 구조체 메모리 할당
	if (!token) // 할당 실패 시
		return (NULL);
	token->type = type; // 타입 설정
	token->value = value; // 값 설정
	token->next = NULL; // 다음 포인터 초기화
	return (token);
}

/*
** 함수 역할: 토큰 리스트의 맨 뒤에 새로운 토큰을 추가.
** @param head 리스트의 헤드 포인터의 주소.
** @param new_node 추가할 새로운 토큰 노드.
*/
void	token_add_back(t_token **head, t_token *new_node)
{
	t_token	*curr;

	if (!new_node) // 추가할 노드가 없으면 리턴
		return ;
	if (*head == NULL) // 리스트가 비어있으면
	{
		*head = new_node; // 헤드를 새 노드로 설정
		return ;
	}
	curr = *head; // 헤드부터 시작
	while (curr->next) // 마지막 노드까지 이동
		curr = curr->next;
	curr->next = new_node; // 마지막 노드 뒤에 연결
}

/*
** 함수 역할: 토큰 리스트 전체의 메모리를 해제.
** @param token 해제할 리스트의 시작 노드.
*/
void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token) // 리스트 순회
	{
		tmp = token; // 현재 노드 저장
		token = token->next; // 다음 노드로 이동
		if (tmp->value)
			free(tmp->value); // 토큰 값(문자열) 해제
		free(tmp); // 노드 메모리 해제
	}
}
