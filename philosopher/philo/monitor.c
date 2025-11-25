/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 08:30:14 by sisung            #+#    #+#             */
/*   Updated: 2025/11/25 13:53:04 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_termination(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&philo->data->dead_mutex);
	is_dead = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (is_dead);
}

static bool	check_if_all_eaten(t_data *data)
{
	size_t	i;
	size_t	count_eaten;

	i = 0;
	count_eaten = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten >= data->must_eat_count)
			count_eaten++;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	if (count_eaten == data->num_of_philos)
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->is_dead = true;
		pthread_mutex_unlock(&data->dead_mutex);
		return (true);
	}
	return (false);
}

static bool	check_if_dead(t_data *data, size_t i)
{
	long long	time_since_last_meal;

	pthread_mutex_lock(&data->philos[i].meal_mutex);
	time_since_last_meal = get_time_ms() - data->philos[i].last_eat_time;
	if (time_since_last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->is_dead = true;
		pthread_mutex_unlock(&data->dead_mutex);
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		print_log(&data->philos[i], "died");
		return (true);
	}
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	return (false);
}

void	monitor_simulation(t_data *data)
{
	size_t	i;

	while (1)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (check_if_dead(data, i))
				return ;
			i++;
		}
		if (data->must_eat_count > 0)
		{
			if (check_if_all_eaten(data))
				return ;
		}
		usleep(1000);
	}
}
