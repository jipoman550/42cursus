/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:34:13 by sisung            #+#    #+#             */
/*   Updated: 2026/02/02 19:24:34 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_word_end_idx(char *str, int i)
{
	char	quote;

	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		if (!quote && ft_isspace(str[i]))
			break ;
		i++;
	}
	return (i);
}

void	split_argv_by_space(t_list **list, char *str)
{
	int		i;
	int		end;
	char	*word;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		end = get_word_end_idx(str, i);
		word = ft_substr(str, i, end - i);
		if (word)
			ft_lstadd_back(list, ft_lstnew(word));
		i = end;
	}
}

void	expand_redirections(t_cmd *cmd, t_shell *sh)
{
	t_redir	*r;
	char	*expanded;
	char	*cleaned;

	r = cmd->redirs;
	while (r)
	{
		if (r->type != R_HEREDOC)
		{
			expanded = expand_str(r->target, sh);
			free(r->target);
			cleaned = remove_quotes(expanded);
			free(expanded);
			r->target = cleaned;
		}
		r = r->next;
	}
}

void	remove_quotes_from_list(t_list *list)
{
	t_list	*curr;
	char	*cleaned;

	curr = list;
	while (curr)
	{
		cleaned = remove_quotes(curr->content);
		free(curr->content);
		curr->content = cleaned;
		curr = curr->next;
	}
}

char	**convert_list_to_argv(t_list *list)
{
	char	**new_argv;
	int		size;
	int		i;
	t_list	*curr;

	size = ft_lstsize(list);
	new_argv = malloc(sizeof(char *) * (size + 1));
	if (!new_argv)
		return (NULL);
	curr = list;
	i = 0;
	while (curr)
	{
		new_argv[i++] = ft_strdup(curr->content);
		curr = curr->next;
	}
	new_argv[i] = NULL;
	return (new_argv);
}
