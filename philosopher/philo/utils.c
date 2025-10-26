/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:06:02 by sisung            #+#    #+#             */
/*   Updated: 2025/10/26 23:55:18 by sisung           ###   ########.fr       */
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

t_data *	clean_data_and_return(t_data *data, char *msg)
{
	size_t	i;

	if (!data)
		return (NULL);
	if (data->forks)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	if (data->philos)
		free(data->philos);
	free(data);
	// 에러 출력하는 것은 printf가 아니라 write 써서 fd 값 맞춰서 해야할듯?
	//printf("%s", msg);
	if (msg)
		write(2, msg, ft_strlen(msg));
	return (NULL);
}

void	finalize_data(t_data *data)
{
	size_t i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	free(data);
}

int	error_and_return(char *msg, int exit_code)
{
	// 여기도 에러 출력 printf말고 다른거 써야할듯?
	//printf("%s", msg);
	if (msg)
		write(2, msg, ft_strlen(msg));
	return (exit_code);
}
