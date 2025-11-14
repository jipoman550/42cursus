/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:59:08 by sisung            #+#    #+#             */
/*   Updated: 2025/11/14 10:47:26 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_data *data)
{
	size_t	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (-1);
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals_eaten = 0;

		// 철학자가 생성되는 순간을 '마지막 식사 시간' 으로 설정 (사망 판정의 기준점)
		data->philos[i].last_eat_time = 0;

		// 왼쪽 포크: 항상 현재 인덱스의 포크
		data->philos[i].l_fork = &data->forks[i];

		// 오른쪽 포크: 다음 인덱스의 포크 (마지막 철학자는 첫 번쨰 포크를 잡음)
		if (i == data->num_of_philos - 1)
			data->philos[i].r_fork = &data->forks[0];
		else
			data->philos[i].r_fork = &data->forks[i + 1];
		i++;
	}
	return (0);
}

static int	init_shared_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (-1);
	}
	data->is_dead = false;
	return (0);
}

static int	init_forks(t_data *data)
{
	size_t	i;

	data->forks = (pthread_mutex_t *)malloc\
(sizeof(pthread_mutex_t) * data->num_of_philos);
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

static int	parse_and_save_args(t_data *data, char **argv, int argc)
{
	long long	val;

	if (parse_required_args(data, argv) != 0)
		return (-1);
	if (argc == 6)
	{
		val = ft_parse_long(argv[5]);
		if (val == -1)
			return (error_and_return(INVALID_EAT_CNT, -1));
		data->must_eat_count = (size_t)val;
	}
	else
		data->must_eat_count = 0;
	return (0);
}

t_data	*init_data(char **argv, int argc)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data));
	if (parse_and_save_args(data, argv, argc) != 0)
		return (clean_data_and_return(data, INVALID_ARG_VAL));
	if (init_forks(data) != 0)
		return (clean_data_and_return(data, ERR_FORK_INIT));
	if (init_shared_mutexes(data) != 0)
		return (clean_data_and_return(data, ERR_SHARED_MUTEX_INIT));

	// t_philo 구조체 배열 초기화
	if (init_philos(data) != 0)
		return (clean_data_and_return(data, ERR_PHILOS_INIT));

	// 시뮬레이션 시작 시간 초기화
	// gettimeofday 사용해서 현재시간을 ms 로 변환하는 함수 필요 (time.c)
	data->start_time = get_time_ms();
	if (data->start_time == -1)
		return (clean_data_and_return(data, ERR_TIME_INIT));

	return (data);
}
