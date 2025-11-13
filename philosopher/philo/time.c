/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:02:46 by sisung            #+#    #+#             */
/*   Updated: 2025/11/14 07:31:19 by sisung           ###   ########.fr       */
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

long long	get_timestamp_ms(t_data *data)
{
	long long	current_time;

	current_time = get_time_ms();
	if (current_time == -1)
		return (-1);
	return (current_time - data->start_time);
}

void	usleep_ms(long long time_to_wait)
{
	long long	start_time;
	long long	current_time;

	start_time = get_time_ms();
	if (start_time == -1)
		return ;

	// 목표 시간이 될 때까지 루프를 돌며 대기 (Busy Waiting 또는 Smart Waiting)
	while (1)
	{
		current_time = get_time_ms();
		if (current_time == -1)
			return ;
		if (current_time >= start_time + time_to_wait)
			break ;
		// OS 스케줄러에게 제어권을 양보하거나 usleep(100) 같은 짧은 대기를 넣어 CPU 점유율을 줄이는 것이 일반적입니다.
		usleep(100);
	}
}
