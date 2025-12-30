/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:07:22 by sisung            #+#    #+#             */
/*   Updated: 2025/12/30 13:52:28 by sisung           ###   ########.fr       */
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

int	error_and_return(char *msg, int exit_code)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	return (exit_code);
}

// 헬퍼 함수: 세마포어와 철학자 자원 정리 (매우 간결해짐)
static void	cleanup_resources(t_data *data)
{
	size_t	i;

	// 1. 글로벌 세마포어 정리 (이미 init에서 unlink 했으므로 close만 수행)
	if (data->forks_sem && data->forks_sem != SEM_FAILED)
		sem_close(data->forks_sem);
	if (data->print_sem && data->print_sem != SEM_FAILED)
		sem_close(data->print_sem);
	if (data->stop_sem && data->stop_sem != SEM_FAILED)
		sem_close(data->stop_sem);

	// 2. 철학자별 개별 세마포어 정리
	if (data->philos)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			// 유효한 세마포어 핸들이 있다면 close만 호출
			if (data->philos[i].meal_sem && data->philos[i].meal_sem != SEM_FAILED)
				sem_close(data->philos[i].meal_sem);
			i++;
		}
		free(data->philos);
	}
}

// 메인 정리 함수
t_data	*clean_data_and_return(t_data *data, char *msg)
{
	if (!data)
		return (NULL);

	// 1. PID 배열 해제
	if (data->pids)
		free(data->pids);

	// 2. 세마포어 핸들 닫기 및 철학자 배열 해제
	cleanup_resources(data);

	// 3. 메인 데이터 구조체 해제
	free(data);

	// 4. 에러 메시지 출력
	if (msg)
		write(2, msg, ft_strlen(msg));

	return (NULL);
}

void	finalize_data(t_data *data)
{
	size_t	i;

	if (!data)
		return ;

	// 1. 글로벌 세마포어 닫기
    // (이미 init에서 unlink 했으므로 close만 하면 시스템이 알아서 회수함)
	if (data->forks_sem != SEM_FAILED)
		sem_close(data->forks_sem);
	if (data->print_sem != SEM_FAILED)
		sem_close(data->print_sem);
	if (data->stop_sem != SEM_FAILED)
		sem_close(data->stop_sem);

	// 2. 철학자별 개별 세마포어 닫기
	if (data->philos)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (data->philos[i].meal_sem != SEM_FAILED)
				sem_close(data->philos[i].meal_sem);
			i++;
		}
		free(data->philos);
	}

	// 3. PID 배열 해제 (보너스에서 추가된 부분)
	if (data->pids)
		free(data->pids);

	// 4. 메인 데이터 해제
	free(data);
}
