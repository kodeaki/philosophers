/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:01:13 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/08 12:01:30 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	If character 'c' is a capital letter, turns it into a lowercase letter,
	otherwise returns the character.										*/
int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
