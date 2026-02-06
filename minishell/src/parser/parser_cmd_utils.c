/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:02:21 by sisung            #+#    #+#             */
/*   Updated: 2026/02/02 20:13:51 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_cmd_list_on_error(t_cmd *head)
{
	t_cmd	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->argv)
			free_str_array(temp->argv);
		if (temp->redirs)
			free_redirs(temp->redirs);
		free(temp);
	}
}

t_redir	*new_redir(t_redir_type type, char *target)
{
	t_redir	*new;

	new = calloc(1, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->target = target;
	new->next = NULL;
	return (new);
}

void	redir_add_back(t_redir **head, t_redir *new)
{
	t_redir	*curr;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

int	count_args(t_token *token)
{
	int	cnt;

	cnt = 0;
	while (token && token->type != T_PIPE)
	{
		if (token->type >= T_REDIR_IN && token->type <= T_REDIR_HEREDOC)
		{
			if (token->next)
				token = token->next;
		}
		else
			cnt++;
		token = token->next;
	}
	return (cnt);
}
