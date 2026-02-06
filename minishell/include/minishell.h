/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:01:06 by hama              #+#    #+#             */
/*   Updated: 2026/02/05 18:45:46 by hama             ###   ########.fr       */
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

extern int	g_exit_code;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	int				is_builtin;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipeline
{
	t_cmd	*cmds;
}	t_pipeline;

typedef struct s_shell
{
	char	**envp;
	int		last_status;
	int		line_count;
	int		should_exit;
}	t_shell;

typedef struct s_mix
{
	int		cmd_cnt;
	int		prev;
	int		pipefd[2];
	int		i;
	pid_t	*pid;
	t_cmd	*cmd;
}	t_mix;

typedef struct s_kv
{
	char	*key;
	char	*value;
}	t_kv;

void	free_str_array(char **arr);
void	free_redirs(t_redir *redirs);
void	free_pipeline(t_pipeline *p);

int		parse_line(const char *line, t_pipeline **out, t_shell *sh);

void	exe_pipeline(t_pipeline *p, t_shell *sh);

void	free_envp(char **envp);

void	set_signal_interactive(void);
void	set_signal_heredoc_child(void);
void	set_signal_heredoc_parent(void);

int		ft_export(t_cmd *cmd, t_shell *sh);

#endif
