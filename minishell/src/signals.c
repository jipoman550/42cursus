/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 10:43:35 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 16:46:39 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 함수 역할: 대화형 모드(Interactive Mode)에서 SIGINT(Ctrl-C) 시그널을 처리하는 핸들러.
** @param signum 발생한 시그널 번호 (여기서는 SIGINT).
*/
static void	handle_sigint(int signum)
{
	(void)signum; // 사용하지 않는 매개변수 경고 방지
	write(1, "\n", 1); // 새로운 줄 출력하여 프롬프트가 다음 줄에 뜨도록 함
	g_exit_code = SIGINT; // 전역 종료 코드를 SIGINT 값으로 설정 (보통 130으로 처리됨)
	rl_on_new_line(); // Readline에게 커서가 새 줄에 있음을 알림
	rl_replace_line("", 0); // 현재 입력 버퍼를 비움
	rl_redisplay(); // 프롬프트를 다시 표시
}

/*
** 함수 역할: 대화형 모드(쉘이 입력을 기다리는 상태)의 시그널 설정을 적용.
*/
void	set_signal_interactive(void)
{
	signal(SIGINT, handle_sigint); // SIGINT(Ctrl-C) 발생 시 handle_sigint 실행
	signal(SIGQUIT, SIG_IGN); // SIGQUIT(Ctrl-\) 무시 (아무 동작 안 함)
}

/*
** 함수 역할: Heredoc 입력 중 자식 프로세스에서 SIGINT를 처리하는 핸들러.
** @param signum 발생한 시그널 번호.
*/
static void	handle_heredoc_sigint(int signum)
{
	(void)signum; // 사용하지 않는 매개변수 경고 방지
	g_exit_code = SIGINT; // 전역 종료 코드 설정
	write(1, "\n", 1); // 줄바꿈 출력
	close(0); // 표준 입력(stdin)을 닫아 readline이 EOF를 인식하게 하여 입력 루프 종료 유도
}

/*
** 함수 역할: Heredoc 실행 중 자식 프로세스의 시그널 설정.
*/
void	set_signal_heredoc_child(void)
{
	signal(SIGINT, handle_heredoc_sigint); // SIGINT 발생 시 handle_heredoc_sigint 실행
	signal(SIGQUIT, SIG_IGN); // SIGQUIT 무시
}

/*
** 함수 역할: Heredoc 실행 중 부모 프로세스의 시그널 설정.
*/
void	set_signal_heredoc_parent(void)
{
	signal(SIGINT, SIG_IGN); // 부모는 SIGINT를 무시 (자식이 처리하고 종료되기를 기다림)
	signal(SIGQUIT, SIG_IGN); // SIGQUIT 무시
}
