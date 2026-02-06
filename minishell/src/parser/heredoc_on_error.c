/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_on_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 21:46:54 by sisung            #+#    #+#             */
/*   Updated: 2026/02/04 13:47:06 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static int	is_error_break_point(t_token *curr)
{
	if (curr->type == T_PIPE)
	{
		if (!curr->next || curr->next->type == T_PIPE)
			return (1);
	}
	else if (curr->type >= T_REDIR_IN && curr->type <= T_REDIR_HEREDOC)
	{
		if (!curr->next || curr->next->type != T_WORD)
			return (1);
	}
	return (0);
}

static void	consume_loop(char *limiter, t_shell *sh)
{
	char	*line;
	int		start_line;

	start_line = sh->line_count;
	while (1)
	{
		line = readline("> ");
		if (g_exit_code == SIGINT || !line || !ft_strcmp(line, limiter))
		{
			if (g_exit_code != SIGINT && !line)
				print_heredoc_warning(start_line, limiter);
			if (line)
				free(line);
			break ;
		}
		sh->line_count++;
		free(line);
	}
}

static void	run_child_process(char *limiter, t_shell *sh, t_token *head)
{
	set_signal_heredoc_child();
	consume_loop(limiter, sh);
	free_tokens(head);
	free_envp(sh->envp);
	if (g_exit_code == SIGINT)
		exit(1);
	exit(0);
}

static int	fork_and_wait(char *limiter, t_shell *sh, t_token *head)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		run_child_process(limiter, sh, head);
	set_signal_heredoc_parent();
	waitpid(pid, &status, 0);
	set_signal_interactive();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		g_exit_code = 1;
		sh->last_status = 130;
		return (1);
	}
	return (0);
}

void	consume_heredoc_on_error(t_token *tokens, t_shell *sh)
{
	t_token	*head;

	head = tokens;
	while (tokens)
	{
		if (is_error_break_point(tokens))
			break ;
		if (tokens->type == T_REDIR_HEREDOC && tokens->next)
		{
			if (fork_and_wait(tokens->next->value, sh, head))
				return ;
		}
		tokens = tokens->next;
	}
}
