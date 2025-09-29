/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:22:06 by tpirinen          #+#    #+#             */
/*   Updated: 2025/09/20 18:02:10 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int	ft_args_valid(int ac, char **av)
{
	int	i;
	int	j;

	if (ac == 5 || ac == 6)
	{
		if (av[1][0] == '0')
			return (false);
		i = 1;
		while (av[i])
		{
			j = 0;
			while (av[i][j])
			{
				if (!(av[i][j] >= '0' && av[i][j] <= '9'))
					return (false);
				j++;
			}
			i++;
		}
	}
	else
		return (false);
	return (true);
}
