/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:21:46 by sisung            #+#    #+#             */
/*   Updated: 2025/11/18 10:29:08 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *philo, const char *status)
{
	long long	timestamp;
	bool		is_dead_check;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->dead_mutex);
	is_dead_check = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	if (is_dead_check && strcmp(status, "died") != 0)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	timestamp = get_timestamp_ms(philo->data);
	if (timestamp < 0)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%lld %zu %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 != 0)
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	else
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}

	// 1. get first fork
	// mutex_trylcok 를 구현하기
	// 철학자가 포크 1개만 쥐고 끝까지 가는 경우를 처리해야할 것 같음.
	// 철학자 수가 홀수 일 때 누구를 먼저 먹이느냐
	// ./philo 3 700 200 200 일 때 1 -> 3 -> 2 이렇게 가는게 좋은데
	// 1 -> 3 -> 1 -> 2 이렇게 간다. 이걸 보완해줘야됨.
	pthread_mutex_lock(first_fork);
	print_log(philo, "has taken a fork");
	if (first_fork == second_fork)
	{
		usleep_ms(philo->data->time_to_die * 2);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	print_log(philo, "has taken a fork");

	// 3. start eating (critical section)
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eat_time = get_time_ms();
	if (philo->last_eat_time == -1)
	{
		// 시뮬레이션 종료 로직 or data->is_dead를 true로 설정해서 모니터 스레드가 종료하도록 유도. 지금 생각으로는 후자가 더 맞는 생각인것 같다.
		pthread_mutex_lock(&philo->data->dead_mutex);
		philo->data->is_dead = true;
		pthread_mutex_unlock(&philo->data->dead_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return ;
	}
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);

	print_log(philo, "is eating");

	// 4. time_to_eat time wait
	usleep_ms(philo->data->time_to_eat);

	// return fork
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
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

