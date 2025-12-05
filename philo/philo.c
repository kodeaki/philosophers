/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 00:36:09 by tpirinen          #+#    #+#             */
/*   Updated: 2025/12/05 20:23:01 by tpirinen         ###   ########.fr       */
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
	// else if (index == m->total_philos - 1)
	// {
	// 	p->fork1 = &m->forks[0];
	// 	p->fork2 = &m->forks[index];
	// }
	// else
	// {
	// 	p->fork1 = &m->forks[index];
	// 	p->fork2 = &m->forks[(index + 1)];
	// }
	p->fork1 = &m->forks[index];
	p->fork2 = &m->forks[(index + 1) % m->total_philos];
	p->waiting = false;
	p->access_granted = false;
}

/**
 * Update 'last_ate', sleep for 'time_to_eat', release forks,
 * update 'access_granted' and 'has_eaten', and indicate whether the
 * philosopher has reached its required eat count.
 *
 * @param p Philosopher eating.
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

void thinking(t_philo *p)
{
	long	slack;
	long	max_think;
	long	time_left;
	long	t_think;
	long	started_thinking;

	slack = p->time_to_die - p->time_to_eat - p->time_to_sleep;
	if (slack <= 0)
		return ;
	max_think = slack / 4;
	if (p->monitor->total_philos % 2 != 0)
		max_think = slack - (slack / 4);
	pthread_mutex_lock(&p->monitor->philo_mutex);
	time_left = p->time_to_die - (current_time() - p->last_ate) - p->time_to_eat;
	pthread_mutex_unlock(&p->monitor->philo_mutex);
	if (time_left <= 0)
		return ;
	t_think = max_think;
	if (t_think > time_left)
		t_think = time_left;
	started_thinking = current_time();
	while (get_stop_simulation(p) == false
			&& (current_time() - started_thinking) < t_think)
		usleep(THINK_DELAY);
}

void stagger_start(t_philo *p)
{
	if (p->id % 2 != 0)
	{
		if (p->monitor->total_philos > 100)
		{
			while (get_stop_simulation(p) == false
				&& (current_time() - get_start_time(p)) < p->time_to_eat)
				usleep(500);
		}
		else
		{
			while (get_stop_simulation(p) == false
			&& (current_time() - get_start_time(p)) < (p->time_to_eat / 2))
				usleep(500);
		}
	}
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

	wait_for_start(p);
	if (p->fork2 == NULL)
		return (handle_single_philo(p));
	stagger_start(p);
	while (get_stop_simulation(p) == false)
	{
		philo_print(p, THINKING);
		if (p->has_eaten != 0)
			thinking(p);
		wait_for(p, THINK_DELAY);
		take_forks(p);
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
