/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:07:32 by sisung            #+#    #+#             */
/*   Updated: 2025/11/25 15:41:41 by sisung           ###   ########.fr       */
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
	bool			is_dead;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;

	struct s_philo	*philos;

}	t_data;

typedef struct s_philo
{
	size_t			id;

	long long		last_eat_time;
	size_t			meals_eaten;
	pthread_mutex_t	meal_mutex;

	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	pthread_t		thread;

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
