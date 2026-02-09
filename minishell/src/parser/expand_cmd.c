/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:35:15 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:38 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: 명령어 인자를 순회하며 환경변수 확장을 수행하고 리스트에 수집.
** @param cmd 명령어 구조체.
** @param arg_list 결과를 저장할 리스트 포인터.
** @param sh 쉘 상태 구조체.
*/
static void	collect_arg_list(t_cmd *cmd, t_list **arg_list, t_shell *sh)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->argv[i]) // 인자 배열 순회
	{
		expanded = expand_str(cmd->argv[i], sh); // 환경변수 확장 수행
		split_argv_by_space(arg_list, expanded); // 공백 기준으로 분리하여 리스트에 추가
		free(expanded); // 확장된 문자열 해제
		i++;
	}
}

/*
** 함수 역할: 명령어의 argv 배열을 확장하고 재구성.
** @param cmd 명령어 구조체.
** @param sh 쉘 상태 구조체.
** @return 성공 시 0, 실패 시 -1.
*/
static int	process_cmd_argv(t_cmd *cmd, t_shell *sh)
{
	t_list	*arg_list;
	char	**new_argv;

	arg_list = NULL;
	collect_arg_list(cmd, &arg_list, sh); // 확장 및 분리 수행
	remove_quotes_from_list(arg_list); // 리스트 내의 따옴표 제거
	new_argv = convert_list_to_argv(arg_list); // 리스트를 다시 배열로 변환
	if (!new_argv)
	{
		ft_lstclear(&arg_list, free); // 실패 시 리스트 해제
		return (-1);
	}
	free_str_array(cmd->argv); // 기존 argv 해제
	cmd->argv = new_argv; // 새로운 argv 연결
	ft_lstclear(&arg_list, free); // 리스트 해제
	return (0);
}

/*
** 함수 역할: 단일 명령어 노드에 대해 확장(인자 및 리다이렉션) 수행.
** @param cmd 명령어 구조체.
** @param sh 쉘 상태 구조체.
** @return 성공 시 0, 실패 시 -1.
*/
static int	expand_cmd_node(t_cmd *cmd, t_shell *sh)
{
	if (process_cmd_argv(cmd, sh) == -1) // 인자 확장 처리
		return (-1);
	expand_redirections(cmd, sh); // 리다이렉션 타겟 확장 처리
	return (0);
}

/*
** 함수 역할: 파이프라인 전체에 대해 확장기(Expander) 실행.
** @param pipeline 파이프라인 구조체.
** @param sh 쉘 상태 구조체.
** @return 성공 시 0, 실패 시 1.
*/
int	run_expander(t_pipeline *pipeline, t_shell *sh)
{
	t_cmd	*curr;

	if (!pipeline || !pipeline->cmds)
		return (0);
	curr = pipeline->cmds;
	while (curr) // 명령어 리스트 순회
	{
		if (expand_cmd_node(curr, sh) == -1) // 각 노드 확장 수행
			return (1);
		curr = curr->next;
	}
	return (0);
}
