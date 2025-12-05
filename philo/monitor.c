/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 00:36:05 by tpirinen          #+#    #+#             */
/*   Updated: 2025/12/02 17:00:35 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Set the 'start_time' and initial 'last_ate' for each philosopher once all
 * threads have been created. (last_ate is set to the start_time so philosophers
 * don't immediately die of starvation) This arranges for a synchronized
 * start time across threads.
 *
 * @param m Monitor containing philosopher array.
 */
static void	start_philo_threads(t_monitor *m)
{
	int64_t	start_time;
	int		i;

	if (m->threads_created < m->total_philos)
		return ;
	i = 0;
	start_time = current_time() + THREAD_START_DELAY;
	pthread_mutex_lock(&m->philo_mutex);
	while (i < m->total_philos)
	{
		m->philos[i].last_ate = start_time;
		m->philos[i].start_time = start_time;
		i++;
	}
	pthread_mutex_unlock(&m->philo_mutex);
}

/**
 * Initialize mutexes, create philosopher threads and call
 * start_philo_threads() to set philosopher threads in motion.
 *
 * @param m Monitor to initialize and use for thread creation.
 * @param args Parsed arguments array.
 * @return 0 on success, -1 on pthread create failure.
 */
int	start_monitor(t_monitor *m, int args[5])
{
	int		i;
	t_philo	*philo;

	i = 0;
	m->total_philos = args[0];
	while (i < m->total_philos)
		pthread_mutex_init(&m->forks[i++], NULL);
	pthread_mutex_init(&m->philo_mutex, NULL);
	i = 0;
	while (i < m->total_philos)
	{
		philo = &m->philos[i];
		philo_init(philo, m, i, args);
		if (pthread_create(&philo->thread, NULL, philo_main, philo) > 0)
		{
			printf("error: pthread_create failure");
			return (-1);
		}
		m->threads_created++;
		i++;
	}
	start_philo_threads(m);
	return (0);
}

/**
 * Inspect all philosophers to detect whether the simulation should end due
 * to a death or all philosophers having eaten the required number of times.
 *
 * @param m Monitor containing philosophers.
 * @param dead_idx Out parameter set to index of dead philosopher (if any).
 * @param must_eat_reached Counter incremented when a philosopher reaches
 * the wanted amount of meals.
 * @return 'EXIT_MONITOR' when simulation must stop, 'CONTINUE_MONITOR'
 * otherwise.
 */
static int	scan_philos(t_monitor *m, int *dead_idx, int *must_eat_reached)
{
	int		i;
	int64_t	now;

	i = 0;
	now = current_time();
	while (i < m->total_philos)
	{
		if (m->philos[i].stop_simulation == true)
			return (EXIT_MONITOR);
		if (m->philos[i].has_eaten == m->philos[i].must_eat)
			(*must_eat_reached)++;
		else if (m->philos[i].last_ate + m->philos[i].time_to_die <= now)
		{
			m->philos[i].stop_simulation = true;
			*dead_idx = i;
			return (EXIT_MONITOR);
		}
		i++;
	}
	return (CONTINUE_MONITOR);
}

/**
 * Main monitor loop: periodically scans philosophers for death or completion,
 * grants fork access to the hungriest philosopher. Stops when philosopher scan
 * returns 'EXIT_MONITOR'. 'dead_idx' is set to -1 as to not signify a
 * specific philosopher. Gets set to the index of the dead philosopher
 * in 'scan_philos'.
 *
 * @param m Monitor structure managing philosophers.
 */
void	loop_monitor(t_monitor *m)
{
	int		i;
	int		dead_idx;
	int		must_eat_reached;

	must_eat_reached = 0;
	while (must_eat_reached < m->total_philos)
	{
		dead_idx = -1;
		must_eat_reached = 0;
		pthread_mutex_lock(&m->philo_mutex);
		if (scan_philos(m, &dead_idx, &must_eat_reached) == EXIT_MONITOR)
		{
			i = 0;
			while (i < m->threads_created)
				m->philos[i++].stop_simulation = true;
			pthread_mutex_unlock(&m->philo_mutex);
			if (dead_idx != -1)
				philo_print(&m->philos[dead_idx], DEAD);
			return ;
		}
		pthread_mutex_unlock(&m->philo_mutex);
		grant_or_deny_fork_access(m);
		usleep(MONITOR_RUNNING_RATE);
	}
}

/**
 * Joins the philo threads and destroys mutexes.
 *
 * @param m Monitor to stop and clean up.
 */
void	stop_monitor(t_monitor *m)
{
	int	i;

	i = 0;
	while (i < m->threads_created)
		pthread_join(m->philos[i++].thread, NULL);
	i = 0;
	while (i < m->total_philos)
		pthread_mutex_destroy(&m->forks[i++]);
	pthread_mutex_destroy(&m->philo_mutex);
}
