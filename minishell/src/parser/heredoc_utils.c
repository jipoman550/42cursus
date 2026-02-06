/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:46:59 by sisung            #+#    #+#             */
/*   Updated: 2026/02/02 20:12:38 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && s1[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*get_tmp_filename(int i)
{
	char	*num_str;
	char	*name;

	num_str = ft_itoa(i);
	name = ft_strjoin(".heredoc_", num_str);
	free(num_str);
	return (name);
}

void	print_heredoc_warning(int start_line, char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(start_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
}

int	write_line_to_fd(int fd, char *line, int quoted, t_shell *sh)
{
	char	*expanded;

	if (!quoted)
	{
		expanded = expand_str(line, sh);
		free(line);
		line = expanded;
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (1);
}
