/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:21:46 by sisung            #+#    #+#             */
/*   Updated: 2025/11/11 13:02:30 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 != 0)
	{
		first_fork = philo->l_fork_id;
		second_fork = philo->r_fork_id;
	}
	else
	{
		first_fork = philo->r_fork_id;
		second_fork = philo->l_fork_id;
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

