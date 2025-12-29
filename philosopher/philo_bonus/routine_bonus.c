/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:21:46 by sisung            #+#    #+#             */
/*   Updated: 2025/12/29 16:17:10 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_log(t_philo *philo, const char *status)
{
	long long	timestamp;
	bool		is_dead_check;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->dead_mutex);
	is_dead_check = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	if (is_dead_check && ft_strcmp(status, "died") != 0)
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

static void	set_fork_and_delay(t_philo *philo, pthread_mutex_t **first_fork, \
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
	if (philo->last_eat_time == -1)
		return (handle_eat_data_error(philo, &first_fork, &second_fork));
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
