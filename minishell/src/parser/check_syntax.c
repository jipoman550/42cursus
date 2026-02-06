/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:19:17 by sisung            #+#    #+#             */
/*   Updated: 2026/02/02 19:19:28 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	print_syntax_error(char *token_val)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_val, 2);
	ft_putstr_fd("'\n", 2);
	return (258);
}

static int	check_pipe_syntax(t_token *token, char **err_token)
{
	if (token->type != T_PIPE)
		return (SYNTAX_OK);
	if (!token->next)
	{
		*err_token = "newline";
		return (E_NEWLINE);
	}
	if (token->next->type == T_PIPE)
	{
		*err_token = token->next->value;
		return (E_TOKEN);
	}
	return (SYNTAX_OK);
}

static int	check_redir_syntax(t_token *token, char **err_token)
{
	if (token->type < T_REDIR_IN || token->type > T_REDIR_HEREDOC)
		return (SYNTAX_OK);
	if (!token->next)
	{
		*err_token = "newline";
		return (E_NEWLINE);
	}
	if (token->next->type != T_WORD)
	{
		*err_token = token->next->value;
		return (E_TOKEN);
	}
	return (SYNTAX_OK);
}

int	check_syntax(t_token *tokens, char **err_token)
{
	int	status;

	*err_token = NULL;
	if (!tokens)
		return (SYNTAX_OK);
	if (tokens->type == T_PIPE)
	{
		*err_token = tokens->value;
		return (E_TOKEN);
	}
	while (tokens)
	{
		status = check_pipe_syntax(tokens, err_token);
		if (status != SYNTAX_OK)
			return (status);
		status = check_redir_syntax(tokens, err_token);
		if (status != SYNTAX_OK)
			return (status);
		tokens = tokens->next;
	}
	return (SYNTAX_OK);
}
