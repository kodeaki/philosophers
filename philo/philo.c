/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 00:36:09 by tpirinen          #+#    #+#             */
/*   Updated: 2025/12/17 03:16:35 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Initialize a 't_philo' structure with parameters from the
 * 'args' array and monitor. Sets fork pointers, time values, and initial flags.
 *
 * @param p Philosopher to initialize.
 * @param m Monitor owning the forks.
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
	else if (p->id == m->total_philos)
	{
		p->fork1 = &m->forks[0];
		p->fork2 = &m->forks[index];
	}
	else
	{
		p->fork1 = &m->forks[index];
		p->fork2 = &m->forks[(index + 1)];
	}
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
 * Function to retain the stagger set with stagger_starting_times().
 * Philosophers think for at least 'min_time_to_think' amount of time;
 * unless time left before the philosopher must eat to avoid dying is less than
 * the minimum.
 * 
 * When total_philos == even || min is set to 25% of slack
 * When total_philos == odd  || min is set to 75% of slack
 * 
 * @param p Philosopher thinking.
 */
static void	thinking(t_philo *p)
{
	int64_t	slack;
	int64_t	min_time_to_think;
	int64_t	time_left;
	int64_t	time_to_think;
	int64_t	last_ate;

	slack = p->time_to_die - p->time_to_eat - p->time_to_sleep;
	if (slack <= 0)
		return ;
	min_time_to_think = slack / 4;
	if (p->monitor->total_philos % 2 != 0)
		min_time_to_think = slack - (slack / 4);
	pthread_mutex_lock(&p->monitor->philo_mutex);
	last_ate = p->last_ate;
	pthread_mutex_unlock(&p->monitor->philo_mutex);
	time_left = p->time_to_die
		- (current_time() - last_ate)
		- p->time_to_eat;
	if (time_left <= 0)
		return ;
	time_to_think = min_time_to_think;
	if (time_to_think > time_left)
		time_to_think = time_left;
	wait_for(p, time_to_think);
}

/**
 * Thread entry point and main loop for a philosopher thread.
 * Waits for the global start time, enters the 
 * think/eat/sleep loop, and exits when the
 * simulation ends or the philosopher reaches its 'must_eat' count.
 *
 * @param arg Pointer to 't_philo' for this thread.
 * @return NULL.
 */
void	*philo_main(void *arg)
{
	t_philo *const	p = (t_philo*) arg;

	wait_for_start_time(p);
	if (p->fork2 == NULL)
		return (handle_single_philo(p));
	stagger_starting_times(p);
	while (get_stop_simulation(p) == false)
	{
		philo_print(p, THINKING);
		if (p->has_eaten != 0 && (p->time_to_eat * 4 > p->time_to_die))
			thinking(p);
		pthread_mutex_lock(p->fork2);
		philo_print(p, TOOK_FORK);
		pthread_mutex_lock(p->fork1);
		philo_print(p, TOOK_FORK);
		if (eat_and_check_saturation(p) == FULL)
			return (NULL);
		philo_print(p, SLEEPING);
		wait_for(p, p->time_to_sleep);
	}
	return (NULL);
}

/**
 * Prints a timestamped state message for a philosopher.
 * Uses 'philo_mutex' to guard 'death_printed' in the monitor
 * structure so that no messages are printed after a death message.
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
