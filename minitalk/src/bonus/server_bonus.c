/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:09:59 by sisung            #+#    #+#             */
/*   Updated: 2025/09/08 19:44:59 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static struct s_state	g_server_state;

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
	static pid_t	client_pid;

	(void) context;
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
	sigset_t			blocked_signals;

	ft_printf("Server PID: %d\n", getpid());
	sigemptyset(&blocked_signals);
	sigaddset(&blocked_signals, SIGUSR1);
	sigaddset(&blocked_signals, SIGUSR2);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = blocked_signals;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
