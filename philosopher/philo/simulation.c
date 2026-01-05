/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:41:26 by sisung            #+#    #+#             */
/*   Updated: 2026/01/05 14:05:01 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_philosophers(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

static int	handle_thread_creation_error(t_data *data, size_t threads_created)
{
	size_t	i;

	pthread_mutex_lock(&data->dead_mutex);
	data->is_dead = true;
	pthread_mutex_unlock(&data->dead_mutex);
	i = 0;
	while (i < threads_created)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (1);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		if (check_termination(philo) == true)
			break ;
		philo_eat(philo);
		if (check_termination(philo) == true)
			break ;
		philo_sleep(philo);
		if (check_termination(philo) == true)
			break ;
		philo_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
		{
			return (handle_thread_creation_error(data, i));
		}
		i++;
	}
	monitor_simulation(data);
	join_philosophers(data);
	return (0);
}
