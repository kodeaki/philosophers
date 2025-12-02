/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 00:36:36 by tpirinen          #+#    #+#             */
/*   Updated: 2025/12/02 15:11:25 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Included libraries	// What is being used from the library
# include <pthread.h>	//	- thread and mutex control functions
# include <sys/time.h>	//	- gettimeofday()
# include <unistd.h>	//	- usleep()
# include <stdlib.h>	//	- malloc() and free()
# include <stdint.h>	//	- INT64_MAX
# include <stdio.h>		//	- printf()
# include <stdbool.h>	//	- type bool, true and false
# include <string.h>	//	- memset()
# include <limits.h>	//	- INT_MAX

# define MONITOR_RUNNING_RATE 100		// (microseconds)
# define THREAD_START_DELAY 10000		// (microseconds)
# define THINK_DELAY 100				// (microseconds)
# define REQUEST_FORK_ACCESS_RATE 100	// (microseconds)
# define WAIT_SEGMENT 100				// (microseconds)

typedef struct s_philo		t_philo;
typedef struct s_monitor	t_monitor;

struct s_monitor
{
	int					total_philos;		// total number of philos
	int					threads_created;	// threads successfully created
	pthread_mutex_t		*forks;				// array of the fork mutexes
	pthread_mutex_t		philo_mutex;		// lock held for various data
	bool				death_printed;		// protected by (philo_mutex)
	t_philo				*philos;			// array of philosophers
};

struct s_philo
{
	t_monitor			*monitor;			// back-pointer to the monitor
	int					id;					// id of the philo starting from 1
	pthread_t			thread;				// thread of the philosopher
	int64_t				time_to_die;
	int64_t				time_to_eat;
	int64_t				time_to_sleep;
	int					must_eat;
	pthread_mutex_t		*fork1;
	pthread_mutex_t		*fork2;
	bool				stop_simulation;	// protected by (philo_mutex)
	int64_t				start_time;			// protected by (philo_mutex)
	int64_t				last_ate;			// protected by (philo_mutex)
	int					has_eaten;			// protected by (philo_mutex)
	bool				waiting;			// protected by (philo_mutex)
	bool				access_granted;		// protected by (philo_mutex)
};

enum e_state
{
	TOOK_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
};

enum e_monitoring
{
	CONTINUE_MONITOR,
	EXIT_MONITOR,
};

enum e_eating
{
	FULL,
	KEEP_EATING,
};

// monitor.c
int		start_monitor(t_monitor *monitor, int args[5]);
void	loop_monitor(t_monitor *monitor);
void	stop_monitor(t_monitor *monitor);

// philo.c
void	philo_init(t_philo *philo, t_monitor *m, int index, int args[5]);
void	*philo_main(void *philo);
void	philo_print(t_philo *p, enum e_state state);

// forks.c
void	grant_or_deny_fork_access(t_monitor *m);
void	request_and_wait_for_fork_access(t_philo *p);
void	take_forks(t_philo *p);

// time.c
int64_t	current_time(void);
void	wait_for_start(t_philo *p);
void	wait_until(t_philo *philo, int64_t target_time);
void	wait_for(t_philo *philo, int64_t duration);

#endif
