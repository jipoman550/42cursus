/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:58:25 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:38 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: Heredoc 입력을 받아 파일 디스크립터에 씀.
** @param fd 임시 파일의 파일 디스크립터.
** @param limiter 종료 구분자.
** @param quoted 구분자의 따옴표 여부 (확장 여부 결정).
** @param sh 쉘 상태 구조체.
*/
static void	heredoc_read_loop(int fd, char *limiter, int quoted, t_shell *sh)
{
	char	*line;
	int		start_line;

	start_line = sh->line_count; // 시작 라인 저장
	while (1) // 무한 루프
	{
		line = readline("> "); // 입력 대기
		if (g_exit_code == SIGINT || !line || ft_strcmp(line, limiter) == 0) // 종료 조건 확인
		{
			if (g_exit_code == SIGINT) // SIGINT인 경우
				free(line);
			else if (!line) // EOF인 경우 경고 출력
				print_heredoc_warning(start_line, limiter);
			else // 구분자와 일치하는 경우
				free(line);
			break ; // 루프 탈출
		}
		sh->line_count++; // 라인 수 증가
		write_line_to_fd(fd, line, quoted, sh); // 파일에 쓰기 (확장 처리 포함)
	}
}

/*
** 함수 역할: 임시 파일을 열고 Heredoc 입력을 저장.
** @param filename 임시 파일 이름.
** @param limiter 종료 구분자.
** @param quoted 따옴표 여부.
** @param sh 쉘 상태 구조체.
** @return 성공 시 0, 실패 시 -1.
*/
static int	write_heredoc_to_file(char *filename, char *limiter, \
	int quoted, t_shell *sh)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644); // 쓰기 모드로 파일 열기
	if (fd < 0)
		return (-1); // 실패 시 반환
	heredoc_read_loop(fd, limiter, quoted, sh); // 입력 루프 실행
	close(fd); // 파일 닫기
	return (0);
}

/*
** 함수 역할: Heredoc 자식 프로세스 종료를 대기하고 결과 처리.
** @param pid 자식 프로세스 ID.
** @param tmp_file 임시 파일 이름.
** @param redir 리다이렉션 구조체.
** @param sh 쉘 상태 구조체.
** @return SIGINT 발생 시 해당 코드, 아니면 0.
*/
static int	wait_heredoc_child(pid_t pid, char *tmp_file, \
								t_redir *redir, t_shell *sh)
{
	int	status;

	set_signal_heredoc_parent(); // 부모 시그널 설정
	waitpid(pid, &status, 0); // 자식 대기
	set_signal_interactive(); // 대화형 시그널 복구
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1) // SIGINT로 종료된 경우
	{
		unlink(tmp_file); // 임시 파일 삭제
		free(tmp_file); // 파일명 메모리 해제
		sh->last_status = 130; // 상태 코드 설정
		return (g_exit_code = SIGINT); // SIGINT 반환
	}
	free(redir->target); // 기존 타겟(구분자) 해제
	redir->target = tmp_file; // 타겟을 임시 파일명으로 교체
	redir->type = R_IN; // 타입을 입력 리다이렉션으로 변경
	return (0);
}

/*
** 함수 역할: 하나의 Heredoc을 처리 (자식 프로세스 생성).
** @param redir 리다이렉션 구조체.
** @param i 임시 파일 인덱스.
** @param sh 쉘 상태 구조체.
** @param p 파이프라인 구조체 (자식에서 해제용).
** @return 성공 시 0, SIGINT 시 비정상 종료 코드.
*/
static int	process_one_heredoc(t_redir *redir, int i, t_shell *sh, \
	t_pipeline *p)
{
	pid_t	pid;
	int		quoted;
	char	*tmp_file;
	char	*limiter;

	quoted = (ft_strchr(redir->target, '\'') || ft_strchr(redir->target, '\"')); // 따옴표 포함 여부 확인
	limiter = remove_quotes(redir->target); // 구분자에서 따옴표 제거
	tmp_file = get_tmp_filename(i); // 고유한 임시 파일명 생성
	pid = fork(); // 프로세스 분기
	if (pid == 0) // 자식 프로세스
	{
		set_signal_heredoc_child(); // 시그널 설정
		write_heredoc_to_file(tmp_file, limiter, quoted, sh); // 파일 쓰기
		free(limiter); // 메모리 해제
		free(tmp_file);
		free_pipeline(p); // 파이프라인 해제
		free_envp(sh->envp); // 환경변수 해제
		if (g_exit_code == SIGINT)
			exit(1);
		exit(0);
	}
	free(limiter); // 부모 프로세스에서 메모리 해제
	return (wait_heredoc_child(pid, tmp_file, redir, sh)); // 자식 대기 및 결과 처리
}

/*
** 함수 역할: 파이프라인 내의 모든 Heredoc을 순차적으로 처리.
** @param pipeline 파이프라인 구조체.
** @param sh 쉘 상태 구조체.
** @return 성공 시 0, 중단 시 1.
*/
int	process_heredocs(t_pipeline *pipeline, t_shell *sh)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		i;
	int		ret;

	cmd = pipeline->cmds; // 명령어 리스트 시작
	i = 0; // 임시 파일 인덱스
	while (cmd) // 명령어 순회
	{
		redir = cmd->redirs; // 리다이렉션 리스트 시작
		while (redir) // 리다이렉션 순회
		{
			if (redir->type == R_HEREDOC) // Heredoc인 경우
			{
				ret = process_one_heredoc(redir, i++, sh, pipeline); // 처리 함수 호출
				if (ret != 0) // 에러/중단 시
					return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
