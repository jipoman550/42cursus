/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:02:46 by sisung            #+#    #+#             */
/*   Updated: 2026/01/01 13:59:09 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time_ms(void)
{
	struct timeval	tv;
	long long		ms;

	if (gettimeofday(&tv, NULL) == -1)
	{
		// 💡 여기서 바로 에러 메시지를 찍고 종료!
		// 이렇게 하면 호출하는 쪽(print_log, philo_eat 등)에서는
		// 일일이 if문을 쓸 필요가 없습니다.
		write(2, ERR_TIME_INIT, ft_strlen(ERR_TIME_INIT));
		exit(1);
	}
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
