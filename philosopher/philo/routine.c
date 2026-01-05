/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:21:46 by sisung            #+#    #+#             */
/*   Updated: 2026/01/05 14:07:34 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *philo, const char *status)
{
	t_data		*pdata;
	bool		is_dead_check;
	long long	now;

	pdata = philo->data;
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->dead_mutex);
	is_dead_check = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	if (is_dead_check && ft_strcmp(status, "died") != 0)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	// printf를 호출할 때 시스템 함수를 2번 호출해서 이렇게 now를 변수로 사용해서 최적화
	now = get_time_ms();
	printf("%lld %zu %s\n", now - pdata->start_time, philo->id,
		status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

static void	set_fork_and_delay(t_philo *philo, pthread_mutex_t **first_fork,
	pthread_mutex_t **second_fork)
{
	if (philo->id % 2 != 0)
	{
		*first_fork = philo->l_fork;
		*second_fork = philo->r_fork;
	}
	else
	{
		*first_fork = philo->r_fork;
		*second_fork = philo->l_fork;
	}
	if (philo->data->num_of_philos % 2 != 0 && (philo->id) % 2 != 0)
		usleep_ms(5);
	else if (philo->data->num_of_philos % 2 == 0 && (philo->id) % 2 == 0)
		usleep_ms(5);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	set_fork_and_delay(philo, &first_fork, &second_fork);
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
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eat_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_log(philo, "is eating");
	usleep_ms(philo->data->time_to_eat);
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
