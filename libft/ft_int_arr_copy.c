/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_arr_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:18:38 by tpirinen          #+#    #+#             */
/*   Updated: 2025/07/23 11:32:59 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Copies 'size' amount of content from 'src' integer array into 'dest'
	integer array.															*/
void	ft_int_arr_copy(int *dest, int *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
}
