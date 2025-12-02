/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 00:36:09 by tpirinen          #+#    #+#             */
/*   Updated: 2025/12/02 17:18:12 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Initialize a 't_philo' structure with parameters from the
 * command-line arguments and monitor. Sets fork pointers, timing
 * values, and initial flags.
 *
 * @param p Philosopher to initialize.
 * @param m Monitor owning shared state (forks, mutexes).
 * @param index Zero-based philosopher index.
 * @param args Array of parsed arguments.
 */
void	philo_init(t_philo *p, t_monitor *m, int index, int args[5])
{
	p->monitor = m;
	p->id = index + 1;
	p->time_to_die = (int64_t)1000 * args[1];
	p->time_to_eat = (int64_t)1000 * args[2];
	p->time_to_sleep = (int64_t)1000 * args[3];
	p->must_eat = args[4];
	if (m->total_philos == 1)
	{
		p->fork1 = &m->forks[0];
		p->fork2 = NULL;
	}
	else if (index == m->total_philos - 1)
	{
		p->fork1 = &m->forks[(index + 1) % m->total_philos];
		p->fork2 = &m->forks[index];
	}
	else
	{
		p->fork1 = &m->forks[index];
		p->fork2 = &m->forks[(index + 1) % m->total_philos];
	}
	p->waiting = false;
	p->access_granted = false;
}

/**
 * Update 'last_ate', sleep for 'time_to_eat', release forks,
 * update 'access_granted' and 'has_eaten', and indicate whether the
 * philosopher has reached its required eat count.
 *
 * @param p Philosopher performing the eat.
 * @return 'FULL' if the philosopher reached 'must_eat', otherwise 'KEEP_EATING'
 */
static int	eat_and_check_saturation(t_philo *p)
{
	philo_print(p, EATING);
	pthread_mutex_lock(&p->monitor->philo_mutex);
	p->last_ate = current_time();
	pthread_mutex_unlock(&p->monitor->philo_mutex);
	wait_for(p, p->time_to_eat);
	pthread_mutex_unlock(p->fork1);
	pthread_mutex_unlock(p->fork2);
	pthread_mutex_lock(&p->monitor->philo_mutex);
	p->access_granted = false;
	p->has_eaten++;
	if (p->has_eaten == p->must_eat)
	{
		pthread_mutex_unlock(&p->monitor->philo_mutex);
		return (FULL);
	}
	pthread_mutex_unlock(&p->monitor->philo_mutex);
	return (KEEP_EATING);
}

/**
 * Special-case lifecycle for the single philosopher scenario: lock the only
 * fork, wait until death, print events and stop the simulation.
 *
 * @param p Philosopher (with 'fork2 == NULL').
 * @return NULL pointer (thread exit value).
 */
static void	*handle_single_philo(t_philo *p)
{
	int64_t	time_to_die;

	pthread_mutex_lock(p->fork1);
	philo_print(p, TOOK_FORK);
	pthread_mutex_lock(&p->monitor->philo_mutex);
	time_to_die = p->time_to_die;
	pthread_mutex_unlock(&p->monitor->philo_mutex);
	wait_for(p, time_to_die);
	pthread_mutex_unlock(p->fork1);
	philo_print(p, DEAD);
	pthread_mutex_lock(&p->monitor->philo_mutex);
	p->stop_simulation = true;
	pthread_mutex_unlock(&p->monitor->philo_mutex);
	return (NULL);
}

/**
 * Thread entry point and main loop for a philosopher thread.
 * Waits for the global start time, enters the 
 * request/take/eat/sleep/think loop, and exits when the
 * simulation ends or the philosopher reaches its 'must_eat' count.
 *
 * @param arg Pointer to 't_philo' for this thread.
 * @return NULL pointer (thread exit value).
 * @thread-safety Uses monitor mutexes and fork mutexes to synchronize with
 * other threads.
 */
void	*philo_main(void *arg)
{
	t_philo *const	p = (t_philo*) arg;

	wait_for_start(p);
	if (p->fork2 == NULL)
		return (handle_single_philo(p));
	while (true)
	{
		philo_print(p, THINKING);
		wait_for(p, THINK_DELAY);
		pthread_mutex_lock(&p->monitor->philo_mutex);
		if (p->stop_simulation == true)
			break ;
		pthread_mutex_unlock(&p->monitor->philo_mutex);
		request_and_wait_for_fork_access(p);
		take_forks(p);
		if (eat_and_check_saturation(p) == FULL)
			return (NULL);
		philo_print(p, SLEEPING);
		wait_for(p, p->time_to_sleep);
	}
	pthread_mutex_unlock(&p->monitor->philo_mutex);
	return (NULL);
}

/**
 * Prints a timestamped state message for a philosopher. Uses
 * 'p->monitor->philo_mutex' to read the philosopher id and start_time
 * and to guard 'death_printed' in the monitor structure so that no messages
 * are printed after a death message.
 *
 * @param p Philosopher whose state is printed.
 * @param state State enumerator indicating which message to print.
 */
void	philo_print(t_philo *p, enum e_state state)
{
	int					timestamp;
	static char *const	state_names[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died",
	};

	pthread_mutex_lock(&p->monitor->philo_mutex);
	if (p->monitor->death_printed == true)
	{
		pthread_mutex_unlock(&p->monitor->philo_mutex);
		return ;
	}
	if (state == DEAD)
		p->monitor->death_printed = true;
	timestamp = (current_time() - p->start_time) / 1000;
	printf("%d %d %s\n", timestamp, p->id, state_names[state]);
	pthread_mutex_unlock(&p->monitor->philo_mutex);
}
