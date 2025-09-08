/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:09:33 by tpirinen          #+#    #+#             */
/*   Updated: 2025/06/01 23:10:11 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Writes the given integer 'n' to the given file descriptor 'fd' and
	returns the number of chars printed. Returns -1 on error.				*/
ssize_t	ft_putnbr_fd(int nbr, int fd)
{
	ssize_t		err;
	ssize_t		chars_printed;
	long long	n;

	n = (long long)nbr;
	chars_printed = 0;
	if (n < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		chars_printed++;
		n = -n;
	}
	if (n > 9)
	{
		err = ft_putnbr_fd((int)(n / 10), fd);
		if (err == -1)
			return (-1);
		chars_printed += err;
	}
	err = ft_putchar_fd((n % 10) + '0', fd);
	if (err == -1)
		return (-1);
	chars_printed += err;
	return (chars_printed);
}
