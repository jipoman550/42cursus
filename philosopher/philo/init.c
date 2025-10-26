/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:59:08 by sisung            #+#    #+#             */
/*   Updated: 2025/10/26 23:57:34 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_shared_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (-1);

	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (-1);
	}

	// 시뮬레이션 시작 시간 초기화
	// gettimeofday 사용해서 현재시간을 ms 로 변환하는 함수 필요 (time.c)
	// data->start_time = get_time_ms();

	data->is_dead = false;

	return (0);
}

static int	init_forks(t_data *data)
{
	size_t	i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (-1);

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i > 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int  parse_and_save_args(t_data *data, char **argv, int argc)
{
	long long	val;
	size_t		i;

	i = 1;
	while (i <= 4)
	{
		val = ft_parse_long(argv[i]);
		if (val == -1)
			return (-1);
		if (i == 1) data->num_of_philos = (size_t)val;
		else if (i == 2) data->time_to_die = val;
		else if (i == 3) data->time_to_eat = val;
		else if (i == 4) data->time_to_sleep = val;
		i++;
	}
	if (argc == 6)
	{
		val = ft_parse_long(argv[5]);
		if (val == -1)
			error_and_return(INVALID_EAT_CNT, -1);
		data->must_eat_count = (size_t)val;
	}
	else
	{
		data->must_eat_count = 0;
	}
	return (0);
}

t_data *	init_data(char **argv, int argc)
{
	t_data *    data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data));
	if (parse_and_save_args(data, argv, argc) != 0)
		return clean_data_and_return(data, INVALID_ARG_VAL);
	if (init_forks(data) != 0)
		return clean_data_and_return(data, ERR_FORK_INIT);
	if (init_shared_mutexes(data) != 0)
		return clean_data_and_return(data, ERR_SHARED_MUTEX_INIT);

	// t_philo 구조체 배열 초기화

	return (data);
}
