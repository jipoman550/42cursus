/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 08:30:14 by sisung            #+#    #+#             */
/*   Updated: 2025/11/17 11:41:08 by sisung           ###   ########.fr       */
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
	long long time_since_last_meal;

	pthread_mutex_lock(&data->philos[i].meal_mutex);

	// 1. Calculate the time elapsed since the last meal
	long long test = get_time_ms();
	time_since_last_meal = test - data->philos[i].last_eat_time; // 이상하다? routine.c에서는 업데이트해주는데, 왜 여기서는 0이 찍힐까?
	printf(" mmss %lld,,,, philo %lld\n", test, data->philos[i].last_eat_time);
	printf("\n%lld\n", time_since_last_meal);
	// 2. Death condition examination
	if (time_since_last_meal > data->time_to_die)
	{
		// 3. Death detection: setting the is_dead flag
		pthread_mutex_lock(&data->dead_mutex);
		data->is_dead = true;
		pthread_mutex_unlock(&data->dead_mutex);
		// 4. Release data_mutex
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		// 5. Death log output
		print_log(&data->philos[i], "died");
		return (true); // detection death
	}
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
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
