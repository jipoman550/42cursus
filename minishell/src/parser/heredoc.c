/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:58:25 by sisung            #+#    #+#             */
/*   Updated: 2026/02/04 13:47:01 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	heredoc_read_loop(int fd, char *limiter, int quoted, t_shell *sh)
{
	char	*line;
	int		start_line;

	start_line = sh->line_count;
	while (1)
	{
		line = readline("> ");
		if (g_exit_code == SIGINT || !line || ft_strcmp(line, limiter) == 0)
		{
			if (g_exit_code == SIGINT)
				free(line);
			else if (!line)
				print_heredoc_warning(start_line, limiter);
			else
				free(line);
			break ;
		}
		sh->line_count++;
		write_line_to_fd(fd, line, quoted, sh);
	}
}

static int	write_heredoc_to_file(char *filename, char *limiter, \
	int quoted, t_shell *sh)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	heredoc_read_loop(fd, limiter, quoted, sh);
	close(fd);
	return (0);
}

static int	wait_heredoc_child(pid_t pid, char *tmp_file, \
								t_redir *redir, t_shell *sh)
{
	int	status;

	set_signal_heredoc_parent();
	waitpid(pid, &status, 0);
	set_signal_interactive();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		unlink(tmp_file);
		free(tmp_file);
		sh->last_status = 130;
		return (g_exit_code = SIGINT);
	}
	free(redir->target);
	redir->target = tmp_file;
	redir->type = R_IN;
	return (0);
}

static int	process_one_heredoc(t_redir *redir, int i, t_shell *sh, \
	t_pipeline *p)
{
	pid_t	pid;
	int		quoted;
	char	*tmp_file;
	char	*limiter;

	quoted = (ft_strchr(redir->target, '\'') || ft_strchr(redir->target, '\"'));
	limiter = remove_quotes(redir->target);
	tmp_file = get_tmp_filename(i);
	pid = fork();
	if (pid == 0)
	{
		set_signal_heredoc_child();
		write_heredoc_to_file(tmp_file, limiter, quoted, sh);
		free(limiter);
		free(tmp_file);
		free_pipeline(p);
		free_envp(sh->envp);
		if (g_exit_code == SIGINT)
			exit(1);
		exit(0);
	}
	free(limiter);
	return (wait_heredoc_child(pid, tmp_file, redir, sh));
}

int	process_heredocs(t_pipeline *pipeline, t_shell *sh)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		i;
	int		ret;

	cmd = pipeline->cmds;
	i = 0;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				ret = process_one_heredoc(redir, i++, sh, pipeline);
				if (ret != 0)
					return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
