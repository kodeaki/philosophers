/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:01:52 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/02 14:59:45 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Copies n bytes from memory area src to memory area dest.
	The memory areas may overlap.											*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*csrc;
	unsigned char	*cdest;

	csrc = (unsigned char *)src;
	cdest = (unsigned char *)dest;
	if (!dest || !src)
		return (dest);
	if (cdest <= csrc)
		while (n--)
			*cdest++ = *csrc++;
	else
		while (n--)
			cdest[n] = csrc[n];
	return (dest);
}
