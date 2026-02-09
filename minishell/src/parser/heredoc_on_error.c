/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_on_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 21:46:54 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:37 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

/*
** 함수 역할: 구문 오류 발생 시 Heredoc 입력을 중단해야 할 지점인지 확인.
** @param curr 현재 토큰.
** @return 중단해야 하면 1, 아니면 0.
*/
static int	is_error_break_point(t_token *curr)
{
	if (curr->type == T_PIPE) // 파이프인 경우
	{
		if (!curr->next || curr->next->type == T_PIPE) // 파이프 뒤가 없거나 또 파이프면 (에러 지점)
			return (1);
	}
	else if (curr->type >= T_REDIR_IN && curr->type <= T_REDIR_HEREDOC) // 리다이렉션인 경우
	{
		if (!curr->next || curr->next->type != T_WORD) // 뒤에 단어가 없으면 (에러 지점)
			return (1);
	}
	return (0); // 에러 지점이 아님
}

/*
** 함수 역할: Heredoc 입력을 받아 소모(저장하지 않음)하는 루프.
** @param limiter 종료 구분자.
** @param sh 쉘 상태 구조체 (라인 카운트 업데이트용).
*/
static void	consume_loop(char *limiter, t_shell *sh)
{
	char	*line;
	int		start_line;

	start_line = sh->line_count; // 시작 라인 저장
	while (1) // 입력 루프
	{
		line = readline("> "); // 프롬프트 출력 및 입력 대기
		if (g_exit_code == SIGINT || !line || !ft_strcmp(line, limiter)) // 시그널, EOF, 또는 구분자 일치 시
		{
			if (g_exit_code != SIGINT && !line) // 강제 종료(EOF)인 경우 경고 출력
				print_heredoc_warning(start_line, limiter);
			if (line)
				free(line); // 라인 메모리 해제
			break ; // 루프 종료
		}
		sh->line_count++; // 라인 카운트 증가
		free(line); // 입력받은 라인은 버림
	}
}

/*
** 함수 역할: 자식 프로세스에서 Heredoc 입력을 처리하고 종료.
** @param limiter 종료 구분자.
** @param sh 쉘 상태 구조체.
** @param head 토큰 리스트 헤드 (메모리 해제용).
*/
static void	run_child_process(char *limiter, t_shell *sh, t_token *head)
{
	set_signal_heredoc_child(); // 자식 프로세스 시그널 설정
	consume_loop(limiter, sh); // 입력 소모 루프 실행
	free_tokens(head); // 토큰 리스트 해제
	free_envp(sh->envp); // 환경변수 해제
	if (g_exit_code == SIGINT) // SIGINT로 종료된 경우
		exit(1);
	exit(0); // 정상 종료
}

/*
** 함수 역할: 자식 프로세스를 생성하여 Heredoc 입력을 처리하고 대기.
** @param limiter 종료 구분자.
** @param sh 쉘 상태 구조체.
** @param head 토큰 리스트 헤드.
** @return SIGINT 발생 시 1, 아니면 0.
*/
static int	fork_and_wait(char *limiter, t_shell *sh, t_token *head)
{
	pid_t	pid;
	int		status;

	pid = fork(); // 프로세스 분기
	if (pid == 0) // 자식 프로세스
		run_child_process(limiter, sh, head);
	set_signal_heredoc_parent(); // 부모 프로세스 시그널 설정 (무시)
	waitpid(pid, &status, 0); // 자식 종료 대기
	set_signal_interactive(); // 대화형 시그널 복구
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1) // 자식이 1로 종료(SIGINT)했으면
	{
		g_exit_code = 1; // 전역 코드 설정
		sh->last_status = 130; // 쉘 상태 설정
		return (1); // 중단 신호 반환
	}
	return (0);
}

/*
** 함수 역할: 구문 오류가 있어도, 오류 지점 이전의 Heredoc은 입력받아 처리(소모).
** @param tokens 토큰 리스트.
** @param sh 쉘 상태 구조체.
*/
void	consume_heredoc_on_error(t_token *tokens, t_shell *sh)
{
	t_token	*head;

	head = tokens; // 해제용 헤드 저장
	while (tokens) // 리스트 순회
	{
		if (is_error_break_point(tokens)) // 구문 오류 발생 지점에 도달하면 중단
			break ;
		if (tokens->type == T_REDIR_HEREDOC && tokens->next) // Heredoc 토큰 발견 시
		{
			if (fork_and_wait(tokens->next->value, sh, head)) // 입력 처리 (SIGINT 시 중단)
				return ;
		}
		tokens = tokens->next; // 다음 토큰
	}
}
