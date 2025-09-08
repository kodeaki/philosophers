/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_low_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 23:15:10 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/20 18:22:45 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*  Prints lowercase hexadecimal to file descriptor. Returns number of
	characters printed or -1 on error.										*/
ssize_t	ft_puthex_low_fd(unsigned int n, int fd)
{
	ssize_t	chars_printed;
	ssize_t	err;

	chars_printed = 0;
	if (n >= 16)
	{
		err = ft_puthex_low_fd(n / 16, fd);
		if (err == -1)
			return (-1);
		chars_printed += err;
	}
	err = write(fd, &HEX_LOWER[n % 16], 1);
	if (err == -1)
		return (-1);
	chars_printed += err;
	return (chars_printed);
}
