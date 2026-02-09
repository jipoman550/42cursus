/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:47:31 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:38 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: 토큰 타입을 리다이렉션 타입으로 변환.
** @param type 토큰 타입.
** @return 대응되는 리다이렉션 타입.
*/
static t_redir_type	get_redir_type(t_token_type type)
{
	if (type == T_REDIR_IN)
		return (R_IN);
	if (type == T_REDIR_OUT)
		return (R_OUT);
	if (type == T_REDIR_HEREDOC)
		return (R_HEREDOC);
	return (R_APPEND);
}

/*
** 함수 역할: 토큰 리스트에서 명령어 인자와 리다이렉션을 추출하여 구조체에 채움.
** @param cmd 채울 명령어 구조체.
** @param tokens 현재 토큰 포인터의 주소 (업데이트됨).
*/
static void	fill_cmd_node(t_cmd *cmd, t_token **tokens)
{
	int		i;
	t_token	*curr;

	i = 0;
	curr = *tokens;
	while (curr && curr->type != T_PIPE) // 파이프를 만나거나 끝날 때까지
	{
		if (curr->type >= T_REDIR_IN && curr->type <= T_REDIR_HEREDOC) // 리다이렉션인 경우
		{
			// 리다이렉션 리스트에 추가 (타입 변환 및 타겟 복제)
			redir_add_back(&cmd->redirs, new_redir(get_redir_type(curr->type), \
				ft_strdup(curr->next->value)));
			curr = curr->next; // 타겟 토큰 건너뛰기
		}
		else // 일반 인자인 경우
		{
			cmd->argv[i] = ft_strdup(curr->value); // 인자 배열에 추가
			i++;
		}
		curr = curr->next; // 다음 토큰
	}
	*tokens = curr; // 외부 포인터 업데이트
}

/*
** 함수 역할: 파싱 중 오류 발생 시 메모리 정리 및 중단.
** @param head 현재까지 생성된 명령어 리스트 헤드.
** @param out 파이프라인 구조체 포인터.
** @return 항상 -1 반환.
*/
static int	abort_parsing(t_cmd *head, t_pipeline **out)
{
	free_cmd_list_on_error(head); // 명령어 리스트 해제
	if (*out)
	{
		free(*out); // 파이프라인 구조체 해제
		*out = NULL;
	}
	return (-1);
}

/*
** 함수 역할: 새로운 명령어 구조체를 할당하고 argv 배열 크기를 계산하여 초기화.
** @param tokens 현재 토큰 리스트 위치.
** @return 초기화된 명령어 구조체 포인터.
*/
static t_cmd	*init_new_cmd(t_token *tokens)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd)); // 구조체 할당 (0으로 초기화)
	if (!new)
		return (NULL);
	new->argv = ft_calloc(count_args(tokens) + 1, sizeof(char *)); // 인자 개수만큼 배열 할당
	if (!new->argv)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

/*
** 함수 역할: 토큰 리스트를 파싱하여 파이프라인 구조체 생성.
** @param tokens 토큰 리스트 헤드.
** @param out 결과 파이프라인을 저장할 포인터.
** @return 성공 시 0, 실패 시 -1.
*/
int	parse_to_cmd(t_token *tokens, t_pipeline **out)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_cmd	*new_cmd;

	head = NULL;
	curr = NULL;
	*out = malloc(sizeof(t_pipeline)); // 파이프라인 구조체 할당
	if (!*out)
		return (-1);
	while (tokens) // 토큰 리스트 순회
	{
		new_cmd = init_new_cmd(tokens); // 새 명령어 노드 초기화
		if (!new_cmd)
			return (abort_parsing(head, out)); // 실패 시 정리
		fill_cmd_node(new_cmd, &tokens); // 노드 내용 채우기
		if (!head)
			head = new_cmd; // 첫 노드 설정
		else
			curr->next = new_cmd; // 리스트 연결
		curr = new_cmd;
		if (tokens && tokens->type == T_PIPE) // 파이프 건너뛰기
			tokens = tokens->next;
	}
	(*out)->cmds = head; // 파이프라인에 명령어 리스트 연결
	return (0);
}
