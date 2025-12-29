/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:07:32 by sisung            #+#    #+#             */
/*   Updated: 2025/12/29 14:41:39 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdbool.h>
# include <bits/pthreadtypes.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

// bonus
# include <semaphore.h>   // sem_open, sem_wait, sem_post, sem_close, sem_unlink
# include <fcntl.h>       // O_CREAT, O_EXCL
# include <sys/stat.h>    // mode constants
# include <sys/wait.h>    // waitpid
# include <signal.h>      // kill

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

typedef struct s_data
{
	size_t			num_of_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	size_t			must_eat_count;

	long long		start_time;
	// bool			is_dead;

	/* --- 세마포어 (기존 뮤텍스 대체) --- */
	sem_t			*forks_sem;	// 탁자 중앙의 포크 더미
	sem_t			*print_sem;	// 로그 출력 보호용
	sem_t			*dead_sem;	// 시뮬레이션 종료 신호용 (선택 사항)

	/* --- 프로세스 관리 --- */
	pid_t			*pids;		// 생성된 자식 프로세스(철학자) ID 저장 배열

	struct s_philo	*philos;	// 철학자들 데이터 배열

}	t_data;

typedef struct s_philo
{
	size_t			id;
	long long		last_eat_time;
	size_t			meals_eaten;

	/* --- 철학자 개인 보호용 --- */
	sem_t			*meal_sem;		// 자신의 식사 시간을 보호할 세마포어 (Named로 생성)
	char			*sem_name;		// 각 개별 세마포어의 이름 (예: "/meal_1")

	/* --- 감시용 스레드 --- */
	pthread_t		monitor_thread;	// 각 프로세스 내부에서 사망을 체크할 스레드

	struct s_data	*data;

}	t_philo;

void		handle_eat_data_error(t_philo *philo, \
	pthread_mutex_t **first_fork, pthread_mutex_t **second_fork);
int			clean_philos_on_fail(size_t i, t_data *data);
t_data		*clean_data_and_return(t_data *data, char *msg);
void		finalize_data(t_data *data);
int			error_and_return(char *msg, int exit_code);

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

int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(char *s);
int			parse_required_args(t_data *data, char **argv);

#endif
