/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:07:22 by sisung            #+#    #+#             */
/*   Updated: 2025/12/29 16:20:27 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	handle_eat_data_error(t_philo *philo, \
	pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	philo->data->is_dead = true;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(*first_fork);
	pthread_mutex_unlock(*second_fork);
}

int	clean_philos_on_fail(size_t i, t_data *data)
{
	while (--i >= 0)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	return (-1);
}

int	error_and_return(char *msg, int exit_code)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	return (exit_code);
}

t_data	*clean_data_and_return(t_data *data, char *msg)
{
	size_t	i;

	if (!data)
		return (NULL);
	if (data->forks)
	{
		i = 0;
		while (i < data->num_of_philos)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	if (data->philos)
		free(data->philos);
	free(data);
	if (msg)
		write(2, msg, ft_strlen(msg));
	return (NULL);
}

void	finalize_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	free(data);
}
