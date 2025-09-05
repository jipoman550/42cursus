/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:33:06 by sisung            #+#    #+#             */
/*   Updated: 2025/09/05 09:10:11 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile int	g_ack_received = 0;

void	handle_ack(int signum)
{
	(void)signum;
	g_ack_received = 1;
}

void	send_message(pid_t pid, const char *str)
{
	size_t				bit_index;

	while (*str)
	{
		bit_index = 8;
		while (bit_index--)
		{
			g_ack_received = 0;
			if ((*str >> bit_index) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			while (!g_ack_received)
			{

			}
		}
		str++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t				pid;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_printf("Usage: ./client [server PID] [string]\n");
		return (1);
	}
	pid = (pid_t)ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("Error: Invalid PID\n");
		return (1);
	}
	sa.sa_handler = handle_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	send_message(pid, argv[2]);
	return (0);
}
