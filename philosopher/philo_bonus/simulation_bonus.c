/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:41:26 by sisung            #+#    #+#             */
/*   Updated: 2025/12/31 16:56:22 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	handle_fork_error(t_data *data, size_t created)
{
	size_t	i;

	i = 0;
	while (i < created)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	write(2, "Error: Fork failed\n", 19);
	return (1);
}

static void	monitor_simulation(t_data *data)
{
	int		status;
	size_t	i;

	// waitpid가 자식 하나라도 종료될 때까지 기다립니다.
	// 누군가 죽으면 exit(1)을 던지도록 구현할 것입니다.
	waitpid(-1, &status, 0);

	// 한 명이라도 죽었거나 문제가 생겼다면 모든 프로세스 강제 종료
	i = 0;
	while (i < data->num_of_philos)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
}

void	philo_routine(t_philo *philo)
{
	// 1. 자식 프로세스 내부에 본인 사망을 감시할 스레드 생성
	// 이 부분은 등록되는 개념인가? 그래서 아래의 eat -> sleep -> think while(1)루프를 도는 동안 monitor_routine 을 계속 동시에? 도는건가?
	// 그래서 만약 먹는 시간이 넘으면 died 를 터미널에 찍고 exit 해버려서 자식 프로세스를 끝내는건가?
	if (pthread_create(&philo->monitor_thread, NULL, monitor_routine, philo) != 0)
	{
		// 생성 실패 시 자원 정리 후 종료
		finalize_data(philo->data);
		exit(1);
	}

	// 이렇게 하면 나중에 join할 필요가 없고, Valgrind도 깨끗하게 통과합니다.
	pthread_detach(philo->monitor_thread);

	// 2. 식사/수면/생각 루프 (맨데토리와 유사하지만 포크는 세마포어)
	if (philo->id % 2 == 0)
		usleep(200); // 데드락 방지를 위한 미세 지연
	while (1)
	{
		philo_eat(philo); // 안에서 meals_eaten 증가

		// 목표 식사 횟수 달성 여부 확인
		// 여기서도 궁금한게 있다. 철학자 3명이 5회 식사하면 된다고 했을 때, 한명이 5회 다먹으면 그 프로세스는 거기서 끝나는거임?
		// 그러면 다른 2명의 철학자는 돌면서 둘 다 5회를 충족하면 그재서야 부모 프로세스에서 끝나는 방식인가? -> 이렇게 해야맞지.
		// 만약 3명 중 1명이 다 먹었다고 부모도 끝나는거는 좀 이상함. pdf에도 안맞을 듯?
		if (philo->data->must_eat_count > 0 && \
			philo->meals_eaten >= philo->data->must_eat_count)
		{
			// 부모에게 '한 명 다 먹었음' 알림
			sem_post(philo->data->full_sem);
			finalize_data(philo->data); // 자식 프로세스가 가진 메모리 복사본 해제
			exit(0); // 정상 종료(식사 완료)
		}
		philo_sleep(philo);
		philo_think(philo);
	}
}

int	start_simulation(t_data *data)
{
	size_t	i;

	i = 0;
	data->start_time = get_time_ms();
	while (i < data->num_of_philos)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			return (handle_fork_error(data, i)); // 실패 시 기존 자식들 kill
		if (data->pids[i] == 0) // 자식 프로세스라면
			philo_routine(&data->philos[i]);
		i++;
	}
    // 부모 프로세스에서 '식사 횟수 감시 스레드' 생성
    if (data->must_eat_count > 0)
    {
        if (pthread_create(&data->full_monitor_thread, NULL, full_monitor_routine, data) != 0)
            return (handle_fork_error(data, data->num_of_philos));
        pthread_detach(data->full_monitor_thread); // 부모는 따로 join 안 하고 detach
    }
	// 부모 프로세스만 여기까지 도달합니다.
	monitor_simulation(data);
	return (0);
}
