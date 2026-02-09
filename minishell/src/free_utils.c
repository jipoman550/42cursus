/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:05:40 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 16:46:39 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*
** 함수 역할: 문자열 배열(char **)을 메모리 해제.
** @param arr 해제할 문자열 배열 (NULL로 끝남).
*/
void	free_str_array(char **arr)
{
	int	i;

	if (!arr) // 배열이 NULL이면 바로 리턴
		return ;
	i = 0;
	while (arr[i]) // NULL 포인터를 만날 때까지 반복
	{
		free(arr[i]); // 각 문자열 메모리 해제
		i++;
	}
	free(arr); // 배열 자체의 메모리 해제
}

/*
** 함수 역할: 리다이렉션 리스트(t_redir)의 메모리를 해제하고 임시 파일 삭제.
** @param redirs 해제할 리다이렉션 리스트의 헤드.
*/
void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs) // 리스트 순회
	{
		tmp = redirs; // 현재 노드 저장
		redirs = redirs->next; // 다음 노드로 이동
		// Heredoc 임시 파일인 경우 파일 삭제 (unlink)
		if (tmp->type == R_IN && tmp->target && \
			ft_strncmp(tmp->target, ".heredoc", 8) == 0)
		{
			unlink(tmp->target); // 파일 시스템에서 파일 삭제
		}
		if (tmp->target)
			free(tmp->target); // 타겟 파일명 문자열 해제
		free(tmp); // 구조체 노드 해제
	}
}

/*
** 함수 역할: 파이프라인 구조체(t_pipeline)와 연결된 모든 명령어, 리다이렉션 메모리 해제.
** @param p 해제할 파이프라인 구조체 포인터.
*/
void	free_pipeline(t_pipeline *p)
{
	t_cmd	*curr;
	t_cmd	*tmp;

	if (!p) // 파이프라인이 NULL이면 리턴
		return ;
	curr = p->cmds; // 명령어 리스트의 헤드
	while (curr) // 명령어 리스트 순회
	{
		tmp = curr; // 현재 명령어 저장
		curr = curr->next; // 다음 명령어로 이동
		free_str_array(tmp->argv); // 명령어 인자 배열 해제
		free_redirs(tmp->redirs); // 리다이렉션 리스트 해제
		free(tmp); // 명령어 구조체 해제
	}
	free(p); // 파이프라인 구조체 해제
}
