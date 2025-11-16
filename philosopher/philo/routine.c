/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:21:46 by sisung            #+#    #+#             */
/*   Updated: 2025/11/16 13:38:25 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *philo, const char *status)
{
	long long	timestamp;

	// 1. check simulation end status
	pthread_mutex_lock(&philo->data->data_mutex);
	if ((philo->data->is_dead == true) && (status = "died"))
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		return ;
	}
	// 이걸 안해줬음.
	pthread_mutex_unlock(&philo->data->data_mutex);

	// 2. start print_mutex lock
	pthread_mutex_lock(&philo->data->print_mutex);

	// 3. calculate flowing time
	timestamp = get_timestamp_ms(philo->data);
	if (timestamp < 0)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}

	// 4. print log to fit shape
	printf("%lld %zu %s\n", timestamp, philo->id, status);

	// 5. stop print_mutex lock
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
	pthread_mutex_lock(first_fork);
	print_log(philo, "has taken a fork");

	// 2. get second fork
	pthread_mutex_lock(second_fork);
	print_log(philo, "has taken a fork");

	// 3. start eating (critical section)
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_eat_time = get_time_ms();
	if (philo->last_eat_time == -1)
	{
		// 시뮬레이션 종료 로직 or data->is_dead를 true로 설정해서 모니터 스레드가 종료하도록 유도. 지금 생각으로는 후자가 더 맞는 생각인것 같다.
		philo->data->is_dead = true;
		pthread_mutex_unlock(&philo->data->data_mutex);
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return ;
	}
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->data_mutex);

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

