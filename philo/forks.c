/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:29:56 by tpirinen          #+#    #+#             */
/*   Updated: 2025/12/05 20:06:02 by tpirinen         ###   ########.fr       */
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
