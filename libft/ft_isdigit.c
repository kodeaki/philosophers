/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:30:55 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/03 17:59:35 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Returns a non-zero value if 'c' is numeric. Otherwise returns 0.		*/
int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}
