/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:21:25 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/20 18:12:35 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Prints an unsigned int to file descriptor and returns number of
	chars printed. Returns -1 on error.										*/
ssize_t	ft_putunbr_fd(unsigned int n, int fd)
{
	ssize_t	err;
	ssize_t	chars_printed;

	chars_printed = 0;
	if (n > 9)
	{
		err = ft_putunbr_fd(n / 10, fd);
		if (err == -1)
			return (err);
		chars_printed += err;
		err = ft_putunbr_fd(n % 10, fd);
		if (err == -1)
			return (-1);
		chars_printed += err;
	}
	else
	{
		n += '0';
		err = write(fd, &n, 1);
		if (err == -1)
			return (-1);
		chars_printed += err;
	}
	return (chars_printed);
}
