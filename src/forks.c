/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:29:56 by tpirinen          #+#    #+#             */
/*   Updated: 2025/11/29 22:03:02 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * Scan waiting philosophers and grant fork access to the hungriest
 * (oldest 'last_ate' timestamp). Updates 'access_granted' under 'philo_mutex'.
 * 'grant_acces_to' is set to -1 as to not signify any specific philosopher
 * until a valid philosopher is found. If no valid philosophers are found,
 * doesn't grant access to any and returns.
 *
 * @param m Monitor deciding whether or not to grant fork access.
 */
void	grant_or_deny_fork_access(t_monitor *m)
{
	int		i;
	int		grant_access_to;
	int64_t	oldest_timestamp;

	i = 0;
	grant_access_to = -1;
	oldest_timestamp = INT64_MAX;
	pthread_mutex_lock(&m->philo_mutex);
	while (i < m->total_philos)
	{
		if (m->philos[i].waiting == true
			&& m->philos[i].access_granted == false)
		{
			if (m->philos[i].last_ate < oldest_timestamp)
			{
				oldest_timestamp = m->philos[i].last_ate;
				grant_access_to = i;
			}
		}
		i++;
	}
	if (grant_access_to != -1)
		m->philos[grant_access_to].access_granted = true;
	pthread_mutex_unlock(&m->philo_mutex);
}

/**
 * Mark the philosopher as waiting and poll 'access_granted' until the
 * monitor grants access or the simulation is stopped.
 *
 * @param p Philosopher requesting forks.
 */
void	request_and_wait_for_fork_access(t_philo *p)
{
	bool	stop_simulation;
	bool	access_granted;
	
	pthread_mutex_lock(&p->monitor->philo_mutex);
	p->waiting = true;
	p->access_granted = false;
	pthread_mutex_unlock(&p->monitor->philo_mutex);
	while (true)
	{
		pthread_mutex_lock(&p->monitor->philo_mutex);
		stop_simulation = p->stop_simulation;
		access_granted = p->access_granted;
		pthread_mutex_unlock(&p->monitor->philo_mutex);
		if (stop_simulation == true)
			return ;
		if (access_granted == true)
			break ;
		usleep(REQUEST_FORK_ACCESS_RATE);
	}
	pthread_mutex_lock(&p->monitor->philo_mutex);
	p->waiting = false;
	pthread_mutex_unlock(&p->monitor->philo_mutex);
}

/**
 * Acquire the two fork mutexes for the philosopher and print take-fork
 * events.
 *
 * @param p Philosopher taking the forks.
 */
void	take_forks(t_philo *p)
{
	pthread_mutex_lock(p->fork1);
	philo_print(p, TOOK_FORK);
	pthread_mutex_lock(p->fork2);
	philo_print(p, TOOK_FORK);
}
