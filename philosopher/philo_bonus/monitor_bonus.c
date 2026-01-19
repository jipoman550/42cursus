/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 08:30:14 by sisung            #+#    #+#             */
/*   Updated: 2026/01/19 09:52:24 by sisung           ###   ########.fr       */
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
	//// 모든 철학자가 다 먹었다면, 부모에게 알려 시뮬레이션 종료
	//sem_wait(data->print_sem); // 메시지 출력 방지용

	//// 자식 프로세스들을 정리하고 프로그램 종료
	//i = 0;
	//while (i < data->num_of_philos)
	//{
	//	kill(data->pids[i], SIGKILL);
	//	i++;
	//}

	// 💡 중요: 부모 프로세스가 죽기 전에 메모리 정리!
	// exit(0) 하면 main으로 돌아가지 않으므로 여기서 직접 치워야 함.
	// 세마포어 close와 free(data->philos), free(data->pids) 등을 수행
	//finalize_data(data);

	// 부모 프로세스 자체를 정상 종료 (Main의 waitpid도 멈춤)
	//exit(0);

	return (NULL);
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
			sem_wait(data->print_sem); // 출력 권한 선점 (다른 메시지 차단)
			printf("%lld %zu died\n", get_time_ms() - data->start_time, philo->id);

			// 2. 부모에게 사망 알림 (exit(1)은 '사망'을 뜻하는 신호로 약속)
			//finalize_data(data);
			exit(1); // 부모에게 사망 보고
			//kill(getpid(), SIGKILL);
		}
		sem_post(philo->meal_sem);
		usleep(1000); // CPU 과부하 방지
	}
	return (NULL);
}
