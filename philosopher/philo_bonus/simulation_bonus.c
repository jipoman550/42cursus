/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:41:26 by sisung            #+#    #+#             */
/*   Updated: 2026/01/19 10:55:09 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	kill_process(t_data *data, size_t created, char *msg)
{
	size_t	i;

	i = 0;
	while (i < created)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	write(2, msg, ft_strlen(msg));
	return (1);
}

/**
 * @brief 식사 횟수 감시 스레드가 종료될 때까지 대기합니다.
 * 누군가 죽어서 시뮬레이션이 끝난 경우, sem_wait에 갇혀 있을 스레드를
 * sem_post로 강제 해제하여 join이 가능하도록 만듭니다.
 */
static void	wait_full_monitor_thread(t_data *data)
{
	size_t	i;

	// 식사 제한 횟수 옵션이 없다면 스레드가 생성되지 않았으므로 리턴
	if (data->must_eat_count == 0)
		return ;

	i = 0;
	// 모니터 스레드가 'sem_wait(data->full_sem)' 루프에서 대기 중일 수 있으므로
	// 철학자 수만큼 post를 던져 루프를 탈출하게 만듭니다.
	while (i < data->num_of_philos)
	{
		sem_post(data->full_sem);
		i++;
	}
	// 스레드가 루프를 탈출하고 종료될 때까지 기다려 자원을 회수합니다.
	pthread_join(data->full_monitor_thread, NULL);
}

static void	monitor_simulation(t_data *data)
{
	int		status;
	size_t	i;
	pid_t	pid;

	// waitpid가 자식 하나라도 종료될 때까지 기다립니다.
	// 누군가 죽으면 exit(1)을 던지도록 구현할 것입니다.
	while (1)
	{
		// 자식 중 누군가 종료될 때까지 대기
		pid = waitpid(-1, &status, 0);
		if (pid == -1) // 더 이상 기다릴 자식 프로세스가 없음
			break ;

		// 자식이 종료되었는데, 'exit(1)' (사망)로 종료된 경우에만 반응이 아니지. exit랑 섞어서 사용해야되나?
		// WIFSIGNALED, WIFEXITED, WEXITSTATUS 각각 무엇을 뜻하는지 알아보기
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			// 누군가 죽었다! -> 나머지 모두 사살
			i = 0;
			while (i < data->num_of_philos)
			{
				kill(data->pids[i], SIGKILL);
				i++;
			}
			break ; // 감시 종료
		}
		// 만약 자식이 식사를 마치고 'exit(0)'으로 죽었다면?
		// 부모는 그냥 무시하고 계속 waitpid로 다른 자식(사망자)을 감시.
		// 그러다 'full_monitor_thread'가 다 찼다고 판단하면 exit(0)을 호출해 프로그램을 끝내기.
	}
}

static void	philo_routine(t_philo *philo)
{
	// 1. 자식 프로세스 내부에 본인 사망을 감시할 스레드 생성
	if (pthread_create(&philo->monitor_thread, NULL, monitor_routine, philo) != 0)
	{
		// 생성 실패 시 자원 정리 후 종료
		//finalize_data(philo->data);
		exit(1);
	}

	// 이렇게 하면 나중에 join할 필요가 없고, Valgrind도 깨끗하게 통과합니다.
	pthread_detach(philo->monitor_thread);

	// 2. 식사/수면/생각 루프 (맨데토리와 유사하지만 포크는 세마포어)
	if (philo->id % 2 == 0)
		usleep_ms(philo->data->time_to_eat / 2); // 데드락 방지를 위한 미세 지연
	while (1)
	{
		philo_eat(philo); // 안에서 meals_eaten 증가

		// 목표 식사 횟수 달성 여부 확인
		if (philo->data->must_eat_count > 0 && \
			philo->meals_eaten >= philo->data->must_eat_count)
		{
			// 부모에게 '한 명 다 먹었음' 알림
			sem_post(philo->data->full_sem);
			//finalize_data(philo->data); // 자식 프로세스가 가진 메모리 복사본 해제
			exit(0); // 정상 종료(식사 완료)
			//kill(getpid(), SIGKILL);
		}
		philo_sleep(philo);
		philo_think(philo);

		// 💡 핵심: 42 환경에서 불공정성을 해결하는 마법의 로직
		// 철학자 수가 홀수일 때, 식사 후 아주 잠깐의 '생각 시간'을 강제함
		if (philo->data->num_of_philos % 2 != 0)
			usleep_ms(1); // 1ms만 쉬어도 스케줄러가 다른 프로세스에 기회를 줍니다.
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
			return (kill_process(data, i, ERR_FORK_FAIL)); // 실패 시 기존 자식들 kill
		if (data->pids[i] == 0) // 자식 프로세스라면
			philo_routine(&data->philos[i]);
		i++;
	}
	// 부모 프로세스에서 '식사 횟수 감시 스레드' 생성
	if (data->must_eat_count > 0)
	{
		if (pthread_create(&data->full_monitor_thread, NULL, full_monitor_routine, data) != 0)
			return (kill_process(data, data->num_of_philos, ERR_THREAD_FAIL));
		// pthread_detach(data->full_monitor_thread); // 부모는 따로 join 안 하고 detach
	}

	// 1. 사망자 발생 또는 전체 식사 완료를 기다림
	monitor_simulation(data);

	// 2. [함수 분리] 감시 스레드 종료 대기 및 자원 회수
	wait_full_monitor_thread(data);
	return (0);
}
