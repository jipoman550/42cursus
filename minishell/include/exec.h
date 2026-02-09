/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:47:04 by hama              #+#    #+#             */
/*   Updated: 2026/02/09 17:49:24 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parser.h"
# include <errno.h>

# define FT_EXIT_OK			0   // 성공
# define FT_EXIT_FAIL		1   // 일반 에러
# define FT_EXIT_EXEC_KO	126 // 실행 불가 (권한 없음 등)
# define FT_EXIT_CMD_N_FND	127 // 명령어를 찾을 수 없음
# define FT_EXIT_SIG		128 // 시그널로 인한 종료 (기본값)

# define FT_HEREDOC_PRE		".herecod"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

/* 파이프라인 및 명령어 실행 */
void	exe_pipeline(t_pipeline *p, t_shell *sh);
int		run_single(t_pipeline *p, t_cmd *cmd, t_shell *sh);

/* 실행 유틸리티 */
int		is_empty_cmd(t_cmd	*cmd);
int		decode_wait_status(int status);
void	set_signal_ign(void);
void	set_signal_dfl(void);
int		cmd_count(t_cmd *c);

/* 파이프 및 프로세스 관리 */
int		err_p_f(pid_t *pid, int i, int prev, int pipefd[2]);
void	pipe_clean_up(t_pipeline *p, t_shell *sh, pid_t *pid, int s);
void	close_fd(int pipe_fd[2]);
int		set_std_inout(int i, int n, t_mix m, t_cmd *cmd);
void	wait_prev_child(pid_t *pid, int count);

/* 리다이렉션 적용 */
int		apply_redirs(t_redir *r);

/* 빌트인 명령어 처리 */
int		is_builtin(const char *str);
int		is_par_builtin(const char *str);
int		exe_builtin(t_pipeline *p, t_cmd *cmd, t_shell *sh);
int		run_single_builtin_in(t_pipeline *p, t_cmd *cmd, t_shell *sh);

/* 환경변수 관리 */
int		env_len(char **envp);
int		env_find(char **envp, char *key);
char	*env_get(char **envp, char *key);
int		env_set(char ***p_envp, char *key, char *value, int eq);
int		env_unset(char ***p_envp, char *key);

/* 환경변수 유틸리티 */
char	**env_dup(char **envp);
void	env_free(char **envp, int flag);

/* 유효성 검사 */
int		print_valid_err(char *cmd, char *arg);
int		valid_key(char *key);

/* 개별 빌트인 함수들 */
int		ft_echo(t_cmd *cmd);
int		ft_cd(t_cmd *cmd, t_shell *sh);
int		ft_pwd(t_cmd *cmd);
int		ft_export(t_cmd *cmd, t_shell *sh);
size_t	key_len(char *str);
int		export_print(char **envp);
int		ft_unset(t_cmd *cmd, t_shell *sh);
int		ft_env(t_pipeline *p, t_cmd *cmd, t_shell *sh);
int		ft_exit(t_cmd *cmd, t_shell *sh);
int		exe_external(t_pipeline *p, t_cmd *cmd, t_shell *sh);

/* 기타 유틸리티 */
void	free_split_hama(char **arr);

#endif
