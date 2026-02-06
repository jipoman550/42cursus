/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 09:58:56 by hama              #+#    #+#             */
/*   Updated: 2026/02/05 20:04:04 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

static int	fd_dup2(const char *path, int flags, int std_fd)
{
	int	fd;

	fd = open(path, flags, 0644);
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		return (perror(NULL), 1);
	}
	if (dup2(fd, std_fd) < 0)
	{
		close(fd);
		return (perror("dup2(rd)"), 1);
	}
	close(fd);
	return (0);
}

int	apply_redirs(t_redir *r)
{
	while (r)
	{
		if (r->type == R_IN || r->type == R_HEREDOC)
		{
			if (fd_dup2(r->target, O_RDONLY, STDIN_FILENO))
				return (1);
		}
		else if (r->type == R_OUT)
		{
			if (fd_dup2(r->target,
					O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO))
				return (1);
		}
		else if (r->type == R_APPEND)
		{
			if (fd_dup2(r->target,
					O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO))
				return (1);
		}
		r = r->next;
	}
	return (0);
}
