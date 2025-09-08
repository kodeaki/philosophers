/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:18:00 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/03 17:59:17 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Returns a non-zero value if 'c' is an ascii character.
	Otherwise returns 0.													*/
int	ft_isascii(int c)
{
	if ((0 <= c && c <= 127))
		return (1);
	else
		return (0);
}
