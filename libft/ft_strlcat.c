/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:10:25 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/03 17:46:51 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Appends the NUL-terminated string 'src' to the end of 'dst'.  It will append
	at most size - ft_strlen(dst) - 1 bytes, NUL-terminating the result.	*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(dst);
	if (!src)
		return (i);
	if (size <= i)
		return (size + ft_strlen(src));
	if (size > 0)
	{
		while (j < size - i - 1 && src[j])
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
	}
	return (i + ft_strlen(src));
}
