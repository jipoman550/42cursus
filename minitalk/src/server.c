/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:09:59 by sisung            #+#    #+#             */
/*   Updated: 2025/09/06 19:00:39 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

struct s_state	g_server_state;

void	process_byte(pid_t client_pid)
{
	if (g_server_state.bit_count == 8)
	{
		if (g_server_state.current_char == '\0')
		{
			write(1, "\n", 1);
			kill(client_pid, SIGUSR1);
		}
		else
		{
			write(1, &g_server_state.current_char, 1);
			kill(client_pid, SIGUSR1);
		}
		g_server_state.current_char = 0;
		g_server_state.bit_count = 0;
	}
	else
		kill(client_pid, SIGUSR1);
}

void	handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	static pid_t	client_pid;

	if (client_pid != info->si_pid)
		client_pid = info->si_pid;
	g_server_state.current_char <<= 1;
	if (signum == SIGUSR2)
		g_server_state.current_char |= 1;
	g_server_state.bit_count++;
	process_byte(client_pid);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
