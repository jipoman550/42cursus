/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:09:59 by sisung            #+#    #+#             */
/*   Updated: 2025/09/05 10:24:10 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

struct s_state	g_server_state;

void	handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	g_server_state.current_char <<= 1;
	if (signum == SIGUSR2)
		g_server_state.current_char |= 1;
	g_server_state.bit_count++;
	if (g_server_state.bit_count == 8)
	{
		write(1, &g_server_state.current_char, 1);
		g_server_state.current_char = 0;
		g_server_state.bit_count = 0;
	}
	kill(info->si_pid, SIGUSR1);
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
