/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:07:32 by sisung            #+#    #+#             */
/*   Updated: 2025/10/14 13:20:38 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdbool.h>

// 시뮬레이션 전체 데이터 및 공유자원 (t_data)
typedef struct s_data
{
	// [인자] 시뮬레이션 설정 값
	size_t			num_of_philos;	// number_of_philosophers
	long long		time_to_die;	// time_to_die (ms)
	long long		time_to_eat;	// time_to_eat (ms)
	long long		time_to_sleep;	// time_to_sleep (ms)
	size_t			must_eat_count;	// [선택 인자] must_eat_count (0이면 무한)

	// [시뮬레이션 상태] 공유 자원
	long long		start_time;		// 시뮬레이션 시작 시간 (gettimeofday)
	bool			is_dead;		// 철학자 사망 여부 (플래그)

	// [동기화] 공유 자원 보호
	pthread_mutex_t	*forks;			// 포크 배열 (각 포크마다 뮤텍스)
	pthread_mutex_t	print_mutex;	// 로그 출력을 위한 뮤텍스
	pthread_mutex_t	data_mutex;		// is_dead, eat_count 등 공유 변수 보호

	// [철학자 배열]
	struct s_philo	*philos;		// t_philo 구조체 배열 포인터 (나중에 할당)

}	t_data;

// 개별 철학자 데이터 (t_philo)
typedef struct s_philo
{
	size_t			id;				// 철학자 번호 (1부터 시작)
	size_t			eat_count;		// 현재까지 식사 횟수
	long long		last_eat_time;	// 마지막으로 식사를 시작한 시간

	// [포크 정보]
	size_t			l_fork_id;		// 왼쪽 포크 인덱스
	size_t			r_fork_id;		// 오른쪽 포크 인덱스

	// [스레드 정보]
	pthread_t		thread;			// 철학자 스레드 핸들

	// [전역 데이터 연결]
	struct s_data	*data;			// t_data 구조체를 가리키는 포인터 (핵심)

}	t_philo;

#endif
