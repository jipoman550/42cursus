/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:18:23 by sisung            #+#    #+#             */
/*   Updated: 2026/02/05 20:03:44 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	g_exit_code = 0;

static void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = env_dup(envp);
	if (!shell->envp)
	{
		perror("env_dup");
		exit(1);
	}
	shell->last_status = 0;
	shell->line_count = 0;
	shell->should_exit = 0;
}

static void	process_pipeline(char *line, t_shell *shell)
{
	t_pipeline	*pipeline;

	add_history(line);
	shell->line_count++;
	pipeline = NULL;
	if (parse_line(line, &pipeline, shell) == 0)
	{
		exe_pipeline(pipeline, shell);
	}
	free_pipeline(pipeline);
}

static void	run_shell(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (g_exit_code == SIGINT)
		{
			shell->last_status = 130;
			g_exit_code = 0;
		}
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line != '\0')
			process_pipeline(line, shell);
		free(line);
		if (shell->should_exit)
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	int			final_status;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	set_signal_interactive();
	run_shell(&shell);
	rl_clear_history();
	final_status = shell.last_status;
	env_free(shell.envp, -1);
	return (final_status);
}
