/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 00:36:27 by tpirinen          #+#    #+#             */
/*   Updated: 2025/11/29 22:12:46 by tpirinen         ###   ########.fr       */
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
void	wait_for_start(t_philo *p)
{
	int64_t	start;

	while (true)
	{
		pthread_mutex_lock(&p->monitor->philo_mutex);
		start = p->start_time;
		pthread_mutex_unlock(&p->monitor->philo_mutex);
		if (start)
			break ;
		wait_for(p, WAIT_SEGMENT);
	}
	wait_until(p, start);
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
	bool	stop_simulation;

	difference = target_time - current_time();
	while (difference > 0)
	{
		pthread_mutex_lock(&p->monitor->philo_mutex);
		stop_simulation = p->stop_simulation;
		pthread_mutex_unlock(&p->monitor->philo_mutex);
		if (stop_simulation == true)
			break ;
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
