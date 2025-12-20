/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 00:36:27 by tpirinen          #+#    #+#             */
/*   Updated: 2025/12/17 02:30:36 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @return Current time in microseconds (int64_t).
 */
int64_t	current_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000000 + timeval.tv_usec);
}

/**
 * Busy-waits (with short sleeps) until the monitor has set the
 * philosopher's 'start_time'. This ensures all threads begin at a common
 * start time.
 *
 * @param p Philosopher whose start_time to wait for.
 */
void	wait_for_start_time(t_philo *p)
{
	while (get_stop_simulation(p) == false && get_start_time(p) == 0)
		wait_for(p, WAIT_SEGMENT);
	wait_until(p, get_start_time(p));
}

/**
 * Delays the starting time for every odd philosopher
 */
void	stagger_starting_times(t_philo *p)
{
	if (p->id % 2 != 0)
	{
		if (p->monitor->total_philos > 100)
		{
			while (get_stop_simulation(p) == false
				&& (current_time() - get_start_time(p)) < p->time_to_eat)
				usleep(WAIT_SEGMENT);
		}
		else
		{
			while (get_stop_simulation(p) == false
				&& (current_time() - get_start_time(p)) < (p->time_to_eat / 2))
				usleep(WAIT_SEGMENT);
		}
	}
}

/**
 * Sleep in short segments until 'target_time', checking 'p->stop_simulation'
 * between segments so the thread doesn't wait unnecessarily
 * when the simulation ends.
 *
 * @param p Philosopher using the wait.
 * @param target_time Absolute time in microseconds to wait until.
 */
void	wait_until(t_philo *p, int64_t target_time)
{
	int64_t	difference;

	difference = target_time - current_time();
	while (get_stop_simulation(p) == false && difference > 0)
	{
		if (difference > WAIT_SEGMENT)
			difference = WAIT_SEGMENT;
		usleep(difference);
		difference = target_time - current_time();
	}
}

/**
 * Convenience wrapper that waits for 'duration' microseconds relative to
 * the current time.
 *
 * @param p Philosopher using the wait.
 * @param duration Duration to wait in microseconds.
 */
void	wait_for(t_philo *p, int64_t duration)
{
	wait_until(p, current_time() + duration);
}
