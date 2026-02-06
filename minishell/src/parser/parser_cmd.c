/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:47:31 by sisung            #+#    #+#             */
/*   Updated: 2026/02/02 19:21:27 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_redir_type	get_redir_type(t_token_type type)
{
	if (type == T_REDIR_IN)
		return (R_IN);
	if (type == T_REDIR_OUT)
		return (R_OUT);
	if (type == T_REDIR_HEREDOC)
		return (R_HEREDOC);
	return (R_APPEND);
}

static void	fill_cmd_node(t_cmd *cmd, t_token **tokens)
{
	int		i;
	t_token	*curr;

	i = 0;
	curr = *tokens;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type >= T_REDIR_IN && curr->type <= T_REDIR_HEREDOC)
		{
			redir_add_back(&cmd->redirs, new_redir(get_redir_type(curr->type), \
				ft_strdup(curr->next->value)));
			curr = curr->next;
		}
		else
		{
			cmd->argv[i] = ft_strdup(curr->value);
			i++;
		}
		curr = curr->next;
	}
	*tokens = curr;
}

static int	abort_parsing(t_cmd *head, t_pipeline **out)
{
	free_cmd_list_on_error(head);
	if (*out)
	{
		free(*out);
		*out = NULL;
	}
	return (-1);
}

static t_cmd	*init_new_cmd(t_token *tokens)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argv = ft_calloc(count_args(tokens) + 1, sizeof(char *));
	if (!new->argv)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

int	parse_to_cmd(t_token *tokens, t_pipeline **out)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_cmd	*new_cmd;

	head = NULL;
	curr = NULL;
	*out = malloc(sizeof(t_pipeline));
	if (!*out)
		return (-1);
	while (tokens)
	{
		new_cmd = init_new_cmd(tokens);
		if (!new_cmd)
			return (abort_parsing(head, out));
		fill_cmd_node(new_cmd, &tokens);
		if (!head)
			head = new_cmd;
		else
			curr->next = new_cmd;
		curr = new_cmd;
		if (tokens && tokens->type == T_PIPE)
			tokens = tokens->next;
	}
	(*out)->cmds = head;
	return (0);
}
