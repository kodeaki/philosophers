/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:49:57 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/03 17:55:10 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Copies up to size - 1 characters from the NUL-terminated string 'src'
	to 'dst', NUL-terminating the result.									*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	length;

	length = 0;
	while (src[length])
	{
		if (length + 1 < size)
			*dst++ = src[length];
		length++;
	}
	if (size > 0)
		*dst = '\0';
	return (length);
}
