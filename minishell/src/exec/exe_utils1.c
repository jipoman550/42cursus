/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:53:16 by hama              #+#    #+#             */
/*   Updated: 2026/02/04 13:54:04 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

int	decode_wait_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	is_empty_cmd(t_cmd	*cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		return (1);
	return (0);
}

void	set_signal_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	cmd_count(t_cmd *c)
{
	int	n;

	n = 0;
	while (c)
	{
		n++;
		c = c->next;
	}
	return (n);
}
