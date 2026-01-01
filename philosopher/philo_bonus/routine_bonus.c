/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:21:46 by sisung            #+#    #+#             */
/*   Updated: 2026/01/01 16:50:55 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_log(t_philo *philo, const char *status)
{
	long long	timestamp;

	// 1. 출력 권한 세마포어 대기
	sem_wait(philo->data->print_sem);

	// 2. 시간 계산
	timestamp = get_time_ms();

	// 3. 로그 출력
	printf("%lld %zu %s\n", timestamp - philo->data->start_time,\
		 philo->id, status);

	// 4. 출력 권한 반납
	sem_post(philo->data->print_sem);
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	// 1. 포크 더미에서 2개를 집어옵니다 (순서 상관 없음)
	sem_wait(data->forks_sem);
	print_log(philo, "has taken a fork");
	sem_wait(data->forks_sem);
	print_log(philo, "has taken a fork");

	// 2. 식사 시간 기록 (자신만의 meal_sem으로 보호)
	sem_wait(philo->meal_sem);
	philo->last_eat_time = get_time_ms();
	print_log(philo, "is eating");
	philo->meals_eaten++;
	sem_post(philo->meal_sem);

	// 3. 식사 수행
	usleep_ms(data->time_to_eat); // 여기서 정밀한 ms 함수 사용

	// 4. 포크 반납 (더미에 다시 넣기)
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
}

void	philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	usleep_ms(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_log(philo, "is thinking");
}
