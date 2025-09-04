/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:33:06 by sisung            #+#    #+#             */
/*   Updated: 2025/09/04 21:26:32 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_message(pid_t pid, const char *str)
{
	size_t	bit_index;

	while (*str)
	{
		bit_index = 8;
		while (bit_index--)
		{
			if ((*str >> bit_index) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
		str++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

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
	send_message(pid, argv[2]);
	return (0);
}
