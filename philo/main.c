/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 00:35:53 by tpirinen          #+#    #+#             */
/*   Updated: 2025/12/02 17:01:40 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Parse a positive integer from a string. Non-digits are ignored.
 * Handles overflow of 'INT_MAX'.
 *
 * @param s Input string containing decimal digits.
 * @return Parsed integer value, -1 if overflows INT_MAX.
 */
static int	parse_nbr(const char *s)
{
	long long	n;

	n = 0;
	while ('0' <= *s && *s <= '9')
	{
		n = n * 10 + (*s - '0');
		if (n > INT_MAX)
			return (-1);
		s++;
	}
	return ((int)n);
}

/**
 * Validate and parse command-line arguments into the 'args' array:
 *  args[0] = number_of_philosophers
 *  args[1] = time_to_die (ms)
 *  args[2] = time_to_eat (ms)
 *  args[3] = time_to_sleep (ms)
 *  args[4] = optional must_eat count or INT_MAX when omitted.
 * Argument values less than or equal to 0 are invalid.
 *
 * @param args Output array of five integers.
 * @return 0 on success, -1 on invalid arguments.
 */
static int	parse_args(int ac, char **av, int args[5])
{
	if (ac < 5 || ac > 6)
		return (-1);
	args[0] = parse_nbr(av[1]);
	args[1] = parse_nbr(av[2]);
	args[2] = parse_nbr(av[3]);
	args[3] = parse_nbr(av[4]);
	if (args[0] <= 0 || args[1] <= 0 || args[2] <= 0 || args[3] <= 0)
		return (-1);
	if (ac == 6)
	{
		args[4] = parse_nbr(av[5]);
		if (args[4] <= 0)
			return (-1);
	}
	else
		args[4] = INT_MAX;
	return (0);
}

/**
 * Free memory allocated to philosophers and forks.
 * 
 * @param m Monitor whose resources should be freed.
 * @return -1 always.
 */
static int	free_forks_and_philos(t_monitor *m)
{
	if (m->forks)
		free(m->forks);
	if (m->philos)
		free(m->philos);
	return (-1);
}

/**
 * Parse arguments, allocate monitor state, start monitor and
 * philosopher threads, and run the monitor loop until the death
 * of a philosopher or 'must_eat' count is reached.
 */
int	main(int ac, char **av)
{
	t_monitor	m;
	int			args[5];

	if (parse_args(ac, av, args) == -1)
	{
		printf("error: invalid argument");
		return (-1);
	}
	memset(&m, 0, sizeof(m));
	m.total_philos = args[0];
	m.forks = malloc(m.total_philos * sizeof(pthread_mutex_t));
	m.philos = malloc(m.total_philos * sizeof(t_philo));
	if (m.forks == NULL || m.philos == NULL)
		return (free_forks_and_philos(&m));
	memset(m.philos, 0, m.total_philos * sizeof(t_philo));
	if (start_monitor(&m, args) == -1)
	{
		stop_monitor(&m);
		return (free_forks_and_philos(&m));
	}
	loop_monitor(&m);
	stop_monitor(&m);
	free_forks_and_philos(&m);
	return (0);
}
