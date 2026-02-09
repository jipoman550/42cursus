/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:01:06 by hama              #+#    #+#             */
/*   Updated: 2026/02/09 17:49:24 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// include/minishell.h

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft2.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>

extern int	g_exit_code; // 전역 변수: 시그널 핸들러와 메인 루프 간 상태 공유

/*
** 리다이렉션 타입을 정의하는 열거형.
** R_IN: < (입력)
** R_OUT: > (출력, 덮어쓰기)
** R_APPEND: >> (출력, 이어쓰기)
** R_HEREDOC: << (히어독)
*/
typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

/*
** 리다이렉션 정보를 담는 구조체.
** type: 리다이렉션 종류.
** target: 파일명 또는 히어독 종료자(limiter).
** next: 다음 리다이렉션 노드.
*/
typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

/*
** 하나의 명령어를 담는 구조체.
** argv: 명령어와 인자 배열 (NULL로 끝남).
** redirs: 해당 명령어에 연결된 리다이렉션 리스트.
** is_builtin: 빌트인 명령어 여부 플래그 (1이면 빌트인).
** next: 파이프로 연결된 다음 명령어.
*/
typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	int				is_builtin;
	struct s_cmd	*next;
}	t_cmd;

/*
** 전체 파이프라인을 관리하는 구조체.
** cmds: 명령어 리스트의 헤드.
*/
typedef struct s_pipeline
{
	t_cmd	*cmds;
}	t_pipeline;

/*
** 쉘의 전반적인 상태를 관리하는 구조체.
** envp: 환경변수 배열 (복제본).
** last_status: 마지막 실행된 명령어의 종료 상태 ($?).
** line_count: 실행된 라인 수 (히어독 경고 메시지 등에 사용).
** should_exit: exit 명령어 실행 시 쉘 종료 플래그.
*/
typedef struct s_shell
{
	char	**envp;
	int		last_status;
	int		line_count;
	int		should_exit;
}	t_shell;

/*
** 파이프라인 실행 시 필요한 변수들을 모아둔 구조체 (Norminette 대응용).
** cmd_cnt: 전체 명령어 개수.
** prev: 이전 파이프의 읽기 fd.
** pipefd: 현재 파이프의 fd 배열.
** i: 현재 명령어 인덱스.
** pid: 자식 프로세스 PID 배열.
** cmd: 현재 실행 중인 명령어 포인터.
*/
typedef struct s_mix
{
	int		cmd_cnt;
	int		prev;
	int		pipefd[2];
	int		i;
	pid_t	*pid;
	t_cmd	*cmd;
}	t_mix;

/*
** 키-값 쌍을 저장하기 위한 구조체 (환경변수 처리 등).
*/
typedef struct s_kv
{
	char	*key;
	char	*value;
}	t_kv;

/* 메모리 해제 관련 함수들 */
void	free_str_array(char **arr);
void	free_redirs(t_redir *redirs);
void	free_pipeline(t_pipeline *p);

/* 파싱 및 실행 진입점 */
int		parse_line(const char *line, t_pipeline **out, t_shell *sh);
void	exe_pipeline(t_pipeline *p, t_shell *sh);

/* 환경변수 해제 */
void	free_envp(char **envp);

/* 시그널 설정 함수들 */
void	set_signal_interactive(void);
void	set_signal_heredoc_child(void);
void	set_signal_heredoc_parent(void);

int		ft_export(t_cmd *cmd, t_shell *sh);

#endif
