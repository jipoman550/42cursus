/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:02:46 by sisung            #+#    #+#             */
/*   Updated: 2026/01/05 13:37:12 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;
	long long		ms;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	usleep_ms(long long time_to_wait)
{
	long long	start_time;
	long long	current_time;

	start_time = get_time_ms();
	while (1)
	{
		current_time = get_time_ms();
		if (current_time >= start_time + time_to_wait)
			break ;
		usleep(100);
	}
}
