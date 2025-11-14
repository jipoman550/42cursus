/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 08:30:14 by sisung            #+#    #+#             */
/*   Updated: 2025/11/14 10:11:22 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_termination(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&philo->data->data_mutex);
	is_dead = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->data_mutex);
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
		pthread_mutex_lock(&data->data_mutex);
		if (data->philos[i].meals_eaten >= data->must_eat_count)
			count_eaten++;
		pthread_mutex_unlock(&data->data_mutex);
		i++;
	}
	if (count_eaten == data->num_of_philos)
	{
		pthread_mutex_lock(&data->data_mutex);
		data->is_dead = true;
		pthread_mutex_unlock(&data->data_mutex);
		return (true);
	}
	return (false);
}

static bool	check_if_dead(t_data *data, size_t i)
{
	long long time_since_last_meal;

	pthread_mutex_lock(&data->data_mutex);

	// 1. Calculate the time elapsed since the last meal
	time_since_last_meal = get_time_ms() - data->philos[i].last_eat_time;

	// 2. Death condition examination
	if (time_since_last_meal > data->time_to_die)
	{
		// 3. Death detection: setting the is_dead flag
		data->is_dead = true;
		// 4. Release data_mutex
		pthread_mutex_unlock(&data->data_mutex);
		// 5. Death log output
		print_log(&data->philos[i], "died");
		return (true); // detection death
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (false); // surviving
}

void	monitor_simulation(t_data *data)
{
	size_t	i;

	while (1)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			// Death verdict
			if (check_if_dead(data, i))
				return ;

			// Determination of num of meals met
			if (data->must_eat_count > 0)
			{
				if (check_if_all_eaten(data))
					return ;
			}
		}
		i++;
	}
	// Wait a moment to reduce CPU usage
	usleep(1000);
}
