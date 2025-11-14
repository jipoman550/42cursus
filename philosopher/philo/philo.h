/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:07:32 by sisung            #+#    #+#             */
/*   Updated: 2025/11/14 10:42:14 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdbool.h>
# include <bits/pthreadtypes.h> // ?? 42 pc에서는 괜찮았는데 왜이럼?
# include <limits.h> // LLONG_MAX를 사용하기 위해 필요
# include <stdio.h>
# include <pthread.h> // pthread_mutex_init 사용
# include <string.h> // memset 사용
# include <unistd.h> // write 함수 사용
# include <sys/time.h> // gettimeofday

# define INVALID_ARGS "Error: Invalid number of arguments.\n"

# define INVALID_EAT_CNT "Error: Invalid argument value for must_eat_count.\n"
# define INVALID_ARG_VAL "Error: Invalid argument value.\n"
# define ERR_FORK_INIT "Failed to initialize a mutex (fork).\n"
# define ERR_SHARED_MUTEX_INIT "Failed to initialize a shared mutex\
 (e.g., print/log lock).\n"
# define ERR_PHILOS_INIT "Failed to initialize a philos array(e.g.,\
 print/log lock).\n"

# define NON_DIGIT_CHAR "Error: Argument contains non-digit characters.\n"
# define EXCEED_MAX_LIMIT "Error: Argument value exceeds maximum limit.\n"
# define CANT_BE_ZERO "Error: Argument cannot be zero.\n"
# define NOT_POSITIVE_INT "Error: Argument must be a positive integer.\n"

# define ERR_THREAD_FAIL "Error: Failed to create thread.\n"

# define ERR_TIME_INIT "Error: Failed to init time.\n"

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
	size_t			meals_eaten;	// must_eat_count 의 수를 세기 위함

	// [포크 정보]
	pthread_mutex_t	*l_fork_id;		// 왼쪽 포크
	pthread_mutex_t	*r_fork_id;		// 오른쪽 포크

	// [스레드 정보]
	pthread_t		thread;			// 철학자 스레드 핸들

	// [전역 데이터 연결]
	struct s_data	*data;			// t_data 구조체를 가리키는 포인터 (핵심)

}	t_philo;

t_data		*init_data(char **argv, int argc);

bool		check_termination(t_philo *philo);
void		monitor_simulation(t_data *data);

long long	ft_parse_long(char *str);

void		print_log(t_philo *philo, const char *status);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

int			start_simulation(t_data *data);

long long	get_time_ms(void);
long long	get_timestamp_ms(t_data *data);
void		usleep_ms(long long time_to_wait);

t_data		*clean_data_and_return(t_data *data, char *msg);
void		finalize_data(t_data *data);
int			error_and_return(char *msg, int exit_code);
int			parse_required_args(t_data *data, char **argv);

#endif
