/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:18:23 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 16:56:24 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	g_exit_code = 0; // 전역 변수: 시그널 핸들러와 메인 루프 간 상태 공유

/*
** 함수 역할: 쉘 구조체 초기화. 환경변수 복제 및 상태 변수 설정.
** @param shell 초기화할 쉘 구조체 포인터.
** @param envp 메인 함수로부터 받은 환경변수 배열.
*/
static void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = env_dup(envp); // 환경변수 복제
	if (!shell->envp) // 복제 실패 시
	{
		perror("env_dup"); // 에러 메시지 출력
		exit(1); // 프로그램 종료
	}
	shell->last_status = 0; // 마지막 종료 상태 초기화
	shell->line_count = 0; // 라인 카운트 초기화
	shell->should_exit = 0; // 종료 플래그 초기화
}

/*
** 함수 역할: 입력된 라인을 파싱하고 파이프라인을 실행.
** @param line 사용자가 입력한 명령어 문자열.
** @param shell 쉘 상태 구조체 포인터.
*/
static void	process_pipeline(char *line, t_shell *shell)
{
	t_pipeline	*pipeline;

	add_history(line); // 입력된 명령어를 히스토리에 추가
	shell->line_count++; // 라인 카운트 증가
	pipeline = NULL; // 파이프라인 포인터 초기화
	// 파싱 수행: 성공 시 0 반환
	if (parse_line(line, &pipeline, shell) == 0)
	{
		exe_pipeline(pipeline, shell); // 파이프라인 실행
	}
	free_pipeline(pipeline); // 실행 후 파이프라인 메모리 해제
}

/*
** 함수 역할: 쉘의 메인 루프 실행 (Read-Eval-Print Loop).
** @param shell 쉘 상태 구조체 포인터.
*/
static void	run_shell(t_shell *shell)
{
	char	*line;

	while (1) // 무한 루프
	{
		line = readline("minishell$ "); // 프롬프트 출력 및 사용자 입력 대기
		if (g_exit_code == SIGINT) // 시그널 핸들러에 의해 SIGINT가 감지된 경우
		{
			shell->last_status = 130; // 종료 상태를 130으로 설정
			g_exit_code = 0; // 전역 변수 초기화
		}
		if (!line) // 입력이 NULL인 경우 (Ctrl-D)
		{
			printf("exit\n"); // exit 메시지 출력
			break ; // 루프 종료
		}
		if (*line != '\0') // 빈 줄이 아닌 경우
			process_pipeline(line, shell); // 파이프라인 처리
		free(line); // readline으로 할당된 메모리 해제
		if (shell->should_exit) // 종료 플래그가 설정된 경우
			break ; // 루프 종료
	}
}

/*
** 함수 역할: 프로그램 진입점. 쉘 초기화 및 실행.
** @param argc 인자 개수 (사용 안 함).
** @param argv 인자 배열 (사용 안 함).
** @param envp 환경변수 배열.
** @return 쉘의 최종 종료 상태.
*/
int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	int			final_status;

	(void)argc; // 사용하지 않는 변수 처리
	(void)argv; // 사용하지 않는 변수 처리
	init_shell(&shell, envp); // 쉘 초기화
	set_signal_interactive(); // 대화형 모드 시그널 설정
	run_shell(&shell); // 쉘 실행 루프 진입
	rl_clear_history(); // 히스토리 정리
	final_status = shell.last_status; // 최종 종료 상태 저장
	env_free(shell.envp, -1); // 환경변수 메모리 해제
	return (final_status); // 종료 상태 반환
}
