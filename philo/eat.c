/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:29:56 by tpirinen          #+#    #+#             */
/*   Updated: 2025/12/17 03:20:41 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	p->has_eaten++;
	pthread_mutex_unlock(&p->monitor->philo_mutex);
	if (get_has_eaten(p) == p->must_eat)
		return (FULL);
	return (KEEP_EATING);
}
