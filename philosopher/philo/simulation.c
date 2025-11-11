/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:41:26 by sisung            #+#    #+#             */
/*   Updated: 2025/11/11 09:40:07 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_thread_creation_error(t_data *data, size_t threads_created)
{
	size_t	i;

	data->is_dead = true;
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
	if (philo->id % 2 == 0)
		usleep_ms(philo->data->time_to_die / 2);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
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
		// 1. Creation thread
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
		{
			return (handle_thread_creation_error(data, i));
		}
		// 2. Start delay to prevent deadlock
		//if (data->num_of_philos % 2 != 0 && (i + 1) % 2 == 0)
		//	usleep(100);
		//else if (data->num_of_philos % 2 == 0 && (i + 1) % 2 != 0)
		//	usleep(100);
		i++;
	}

	// 3. Monitoring start and thread join
	// call monitoring func.

	return (0);
}
