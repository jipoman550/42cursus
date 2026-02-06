/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 08:17:31 by sisung            #+#    #+#             */
/*   Updated: 2026/02/02 19:18:43 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	add_redir_token(char *line, int *i, char c, t_token **head)
{
	if (line[*i + 1] == c)
	{
		if (c == '<')
			token_add_back(head, new_token(T_REDIR_HEREDOC, ft_strdup("<<")));
		else
			token_add_back(head, new_token(T_REDIR_APPEND, ft_strdup(">>")));
		(*i) += 2;
	}
	else
	{
		if (c == '<')
			token_add_back(head, new_token(T_REDIR_IN, ft_strdup("<")));
		else
			token_add_back(head, new_token(T_REDIR_OUT, ft_strdup(">")));
		(*i)++;
	}
}

static int	tokenize_operator(char *line, int *i, t_token **head)
{
	char	c;

	c = line[*i];
	if (c == '|')
	{
		token_add_back(head, new_token(T_PIPE, ft_strdup("|")));
		(*i)++;
		return (1);
	}
	else if (c == '<' || c == '>')
	{
		add_redir_token(line, i, c, head);
		return (1);
	}
	return (0);
}

static int	scan_word_end(char *line, int i, int *end_idx)
{
	char	quote;

	quote = 0;
	while (line[i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '\"'))
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		if (!quote && is_metachar(line[i]))
			break ;
		i++;
	}
	*end_idx = i;
	if (quote != 0)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		return (-1);
	}
	return (0);
}

static int	tokenize_word(char *line, int *i, t_token **head)
{
	int		start;
	int		end;
	char	*word;

	start = *i;
	if (scan_word_end(line, *i, &end) == -1)
		return (-1);
	word = ft_substr(line, start, end - start);
	if (!word)
		return (-1);
	token_add_back(head, new_token(T_WORD, word));
	*i = end;
	return (0);
}

t_token	*lexer(char *line)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (tokenize_operator(line, &i, &head))
			continue ;
		if (tokenize_word(line, &i, &head) == -1)
		{
			free_tokens(head);
			return (NULL);
		}
	}
	return (head);
}
