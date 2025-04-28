/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:01:48 by jdupuis           #+#    #+#             */
/*   Updated: 2025/04/28 03:12:21 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <err.h>
#include <errno.h>

# define RST	"\033[0m"
# define RED	"\033[1;31m"
# define G		"\033[1;32m"
# define Y		"\033[1;33m"
# define B		"\033[1;34m"
# define M		"\033[1;35m"
# define C		"\033[1;36m"
# define W		"\033[1;37m"

#define DEBUG_MODE 0

typedef enum	e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}				t_philo_status;

typedef	enum	e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}				t_opcode;

typedef	enum	e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}				t_time_code;

typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

typedef struct	s_fork
{
	int		fork_id;
	t_mtx	fork;
	
}				t_fork;

typedef struct	s_philo
{
	bool		full;
	int			id;
	long		meals_counter;
	long		last_meal_time;
	pthread_t	thread_id;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
	t_mtx		philo_mutex;
}				t_philo;

struct	s_table
{
	bool		all_threads_ready;
	bool		end_simulation;
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
};

//utils
long	gettime(t_time_code time_code);
void	error_exit(const char *error);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);

//parsing
void	parsing(t_table *table, char **av);

//safe_functions
void	*safe_malloc(size_t bytes);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);

//init
void	data_init(t_table *table);

//dinner
void	dinner_start(t_table *table);
void	thinking(t_philo *philo, bool pre_simulation);

//getters and setter
bool	simulation_finished(t_table *table);
long	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
void	set_long(t_mtx *mutex, long *dest, long value);

//sync_utils
void	wait_all_threads(t_table *table);
void	increase_long(t_mtx *mutex, long *value);
void	de_synchronize_philos(t_philo *philo);
bool	all_threads_are_running(t_mtx *mutex, long *threads, long philo_nbr);

//write
void	write_status(t_philo_status status, t_philo *philo, bool debug);

//monitiring
void	*monitor_dinner(void *data);

#endif