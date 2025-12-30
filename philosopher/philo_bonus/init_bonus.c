/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:59:08 by sisung            #+#    #+#             */
/*   Updated: 2025/12/30 13:37:35 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*get_sem_name(const char *prefix, size_t id)
{
	char	*id_str;
	char	*res;

	id_str = ft_itoa(id); // 숫자를 문자열로 변환 (직접 만든 함수)
	if (!id_str)
		return (NULL);
	res = ft_strjoin(prefix, id_str); // "/philo_meal_" + "1" 합치기
	free(id_str);
	return (res);
}

static int	init_philos(t_data *data)
{
	size_t	i;
	char	*sem_name;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (-1);
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_eat_time = data->start_time;

		// 1. 각 철학자마다 고유한 이름 생성 (예: /meal_1, /meal_2 ...)
		sem_name = get_sem_name("/philo_meal_", i + 1);
		sem_unlink(sem_name); // 혹시 남아있을지 모르는 이전 실행의 찌꺼기 제거

		// 2. 세마포어 열기
		data->philos[i].meal_sem = sem_open(sem_name, O_CREAT, 0644, 1);

		// 3. 생성 성공 시 시스템 목록에서 이름 즉시 제거 (이게 핵심!)
		if (data->philos[i].meal_sem != SEM_FAILED)
			sem_unlink(sem_name);
		free(sem_name);

		if (data->philos[i].meal_sem == SEM_FAILED)
			return (-1);
		i++;
	}
	return (0);
}

static int	init_semaphores(t_data *data)
{
	// 1. 기존에 남아있을지 모르는 세마포어 이름을 시스템에서 제거 (필수)
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_stop");

	// 2. 포크 세마포어: 초기값은 철학자의 수 (누구나 집어갈 수 있는 포크 더미)
	data->forks_sem = sem_open("/philo_forks", O_CREAT, 0644, data->num_of_philos);
	sem_unlink("/philo_forks");

	// 3. 출력 보호 세마포어: 초기값 1 (뮤텍스처럼 동작)
	data->print_sem = sem_open("/philo_print", O_CREAT, 0644, 1);
	sem_unlink("/philo_print");

	// 4. 종료 신호 세마포어: 초기값 0 (누군가 죽었을 때 신호를 기다리는 용도 등)
	data->stop_sem = sem_open("/philo_stop", O_CREAT, 0644, 0);
	sem_unlink("/philo_stop");

	if (data->forks_sem == SEM_FAILED || data->print_sem == SEM_FAILED
		|| data->stop_sem == SEM_FAILED)
		return (-1);
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

	// 1. PID를 저장할 메모리 할당 (프로세스 관리용)
	data->pids = (pid_t *)malloc(sizeof(pid_t) * data->num_of_philos);
	if (!data->pids)
		return (clean_data_and_return(data, ERR_MALLOC));

	// 2. 세마포어 초기화
	if (init_semaphores(data) != 0)
		return (clean_data_and_return(data, ERR_SEM_INIT));

	data->start_time = get_time_ms();
	if (data->start_time == -1)
		return (clean_data_and_return(data, ERR_TIME_INIT));

	// 3. 철학자 구조체 및 개별 세마포어 초기화
	if (init_philos(data) != 0)
		return (clean_data_and_return(data, ERR_PHILOS_INIT));

	return (data);
}
