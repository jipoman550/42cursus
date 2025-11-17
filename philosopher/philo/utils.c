/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:06:02 by sisung            #+#    #+#             */
/*   Updated: 2025/11/17 09:48:37 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
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

// How about detach this func. another .c file?
// Ex) init_utils.c
int	parse_required_args(t_data *data, char **argv)
{
	long long	val;
	size_t		i;

	i = 1;
	while (i <= 4)
	{
		val = ft_parse_long(argv[i]);
		if (val == -1)
			return (-1);
		if (i == 1)
			data->num_of_philos = (size_t)val;
		else if (i == 2)
			data->time_to_die = val;
		else if (i == 3)
			data->time_to_eat = val;
		else if (i == 4)
			data->time_to_sleep = val;
		i++;
	}
	return (0);
}
