/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:09:59 by sisung            #+#    #+#             */
/*   Updated: 2025/09/03 20:02:30 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;

	if (signum == SIGUSR1)
		ft_printf("Received SIGUSR1\n");
	else if (signum == SIGUSR2)
		ft_printf("Received SIGUSR2\n");
}

int main(void)
{
	struct	sigaction	sa;

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
