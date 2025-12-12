/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 19:15:26 by tpirinen          #+#    #+#             */
/*   Updated: 2025/12/08 16:38:26 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_stop_simulation(t_philo *p)
{
	bool	stop_simulation;

	pthread_mutex_lock(&p->monitor->philo_mutex);
	stop_simulation = p->stop_simulation;
	pthread_mutex_unlock(&p->monitor->philo_mutex);
	return (stop_simulation);
}

int64_t	get_start_time(t_philo *p)
{
	int64_t	start_time;

	pthread_mutex_lock(&p->monitor->philo_mutex);
	start_time = p->start_time;
	pthread_mutex_unlock(&p->monitor->philo_mutex);
	return (start_time);
}
