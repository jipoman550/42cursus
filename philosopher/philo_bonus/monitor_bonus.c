/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 08:30:14 by sisung            #+#    #+#             */
/*   Updated: 2025/12/30 16:29:36 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*full_monitor_routine(void *data_ptr)
{
	t_data	*data;
	size_t	i;

	data = (t_data *)data_ptr;
	i = 0;
	// 모든 철학자가 배부를 때까지 sem_wait를 반복
	while (i < data->num_of_philos)
	{
		sem_wait(data->full_sem);
		i++;
	}
	// 모든 철학자가 다 먹었다면, 부모에게 알려 시뮬레이션 종료
	sem_wait(data->print_sem); // 메시지 출력 방지용
	exit(0); // 부모에게 '모두 식사 완료' 신호
}

void	*monitor_routine(void *philo_ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_ptr;
	data = philo->data;
	while (1)
	{
		// 식사 시간 보호를 위해 meal_sem 잠금
		sem_wait(philo->meal_sem);
		if (get_time_ms() - philo->last_eat_time > data->time_to_die)
		{
			// 1. 출력 권한 획득 (사망 메시지 출력 후 아무도 출력 못 하게 함)
			sem_wait(data->print_sem);
			printf("%lld %zu died\n", get_time_ms() - data->start_time, philo->id);

			// 2. 부모에게 사망 알림 (exit(1)은 '사망'을 뜻하는 신호로 약속)
			// 자식 프로세스가 exit() 해버리면 자식 프로세스에 할당된 메모리는 어떻게 할건데~
			exit(1);
		}
		sem_post(philo->meal_sem);
		usleep(1000); // CPU 과부하 방지 ?? 이게 뭔말임. 없으면 어떻게 되는건데~
	}
	return (NULL);
}
