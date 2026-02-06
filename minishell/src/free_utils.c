/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:05:40 by sisung            #+#    #+#             */
/*   Updated: 2026/02/02 20:10:25 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		if (tmp->type == R_IN && tmp->target && \
			ft_strncmp(tmp->target, ".heredoc", 8) == 0)
		{
			unlink(tmp->target);
		}
		if (tmp->target)
			free(tmp->target);
		free(tmp);
	}
}

void	free_pipeline(t_pipeline *p)
{
	t_cmd	*curr;
	t_cmd	*tmp;

	if (!p)
		return ;
	curr = p->cmds;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free_str_array(tmp->argv);
		free_redirs(tmp->redirs);
		free(tmp);
	}
	free(p);
}
