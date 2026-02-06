/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:04:15 by sisung            #+#    #+#             */
/*   Updated: 2026/02/04 09:03:26 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	handle_syntax_error(t_token *tokens, int type, \
								char *err, t_shell *sh)
{
	if (type == E_TOKEN)
		print_syntax_error(err);
	consume_heredoc_on_error(tokens, sh);
	if (g_exit_code != SIGINT && type == E_NEWLINE)
		print_syntax_error(err);
	free_tokens(tokens);
	sh->last_status = 258 % 256;
	return (258);
}

int	parse_line(const char *line, t_pipeline **out, t_shell *sh)
{
	t_token	*tokens;
	char	*err_token;
	int		syntax_type;

	tokens = lexer((char *)line);
	if (!tokens)
		return (-1);
	err_token = NULL;
	syntax_type = check_syntax(tokens, &err_token);
	if (syntax_type != SYNTAX_OK)
		return (handle_syntax_error(tokens, syntax_type, err_token, sh));
	if (parse_to_cmd(tokens, out) == -1)
	{
		free_tokens(tokens);
		ft_putstr_fd("minishell: memory allocation error\n", 2);
		return (1);
	}
	free_tokens(tokens);
	if (process_heredocs(*out, sh) || run_expander(*out, sh))
	{
		free_pipeline(*out);
		*out = NULL;
		return (1);
	}
	return (0);
}
