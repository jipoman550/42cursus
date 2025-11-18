/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:41:26 by sisung            #+#    #+#             */
/*   Updated: 2025/11/18 09:05:46 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_philosophers(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		// pthread_join 호출: 해당 스레드가 종료될 때까지 메인 스레드를 블록.
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
	// Initial start delay (auxiliary safety device)
	//if (philo->id % 2 == 0)
	//	usleep_ms(philo->data->time_to_die / 2);
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
		// 1. Creation thread
		// 각 생성되는 thread 마다
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
	monitor_simulation(data);

	// Wait for all philo threads to terminate and reclaim resources
	join_philosophers(data);

	return (0);
}
