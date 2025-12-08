/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_and_eat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:29:56 by tpirinen          #+#    #+#             */
/*   Updated: 2025/12/08 16:21:04 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Acquire the two fork mutexes for the philosopher and print take-fork
 * events.
 *
 * @param p Philosopher taking the forks.
 */
void	take_forks(t_philo *p)
{
	if (p->id == p->monitor->total_philos)
	{
		pthread_mutex_lock(p->fork1);
		philo_print(p, TOOK_FORK);
		pthread_mutex_lock(p->fork2);
		philo_print(p, TOOK_FORK);
	}
	else
	{
		pthread_mutex_lock(p->fork2);
		philo_print(p, TOOK_FORK);
		pthread_mutex_lock(p->fork1);
		philo_print(p, TOOK_FORK);
	}
}

/**
 * Update 'last_ate', sleep for 'time_to_eat', release forks,
 * update 'access_granted' and 'has_eaten', and indicate whether the
 * philosopher has reached its required eat count.
 *
 * @param p Philosopher eating.
 * @return 'FULL' if the philosopher reached 'must_eat', otherwise 'KEEP_EATING'
 */
int	eat_and_check_saturation(t_philo *p)
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
