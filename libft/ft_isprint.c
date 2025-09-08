/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:21:38 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/03 18:01:00 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Returns a non-zero value if 'c' is a printable ascii character.
	Otherwise returns 0.													*/
int	ft_isprint(int c)
{
	if ((32 <= c && c <= 126))
		return (1);
	else
		return (0);
}
