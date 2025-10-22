/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:06:02 by sisung            #+#    #+#             */
/*   Updated: 2025/10/23 07:35:49 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	size_t	i;

	// 포크 뮤텍스 파괴 (초기화 성공한 경우에만)
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

	// 철학자 배열 해제
	if (data->philos)
		free(data->philos);

	// 최종적으로 t_data 구조체 자체 해제
	free(data);
}

void	destroy_and_free(t_data *data)
{
	size_t i;

	// 1. 포크 뮤텍스 배열 파괴
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}

	// 2. 공유 뮤텍스 파괴 (성공적으로 init이 완료된 상태이므로 안전하게 destroy)
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->data_mutex);

	// 3. 메모리 해제 (포크 배열, 철학자 배열, data 구조체 자체)
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	free(data); // t_data 구조체 자체 해제
}
