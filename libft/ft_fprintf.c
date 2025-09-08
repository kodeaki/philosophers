/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:45:33 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/14 21:13:05 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	ft_parse_args(int fd, char specifier, va_list args);
static ssize_t	ft_loop_s(int fd, va_list args, const char *s, ssize_t err);

/*	First argument serves as the file descriptor to print to.		*/
int	ft_fprintf(int fd, const char *s, ...)
{
	va_list	args;
	ssize_t	total;

	if (!s)
		return (-1);
	total = 0;
	va_start(args, s);
	total = ft_loop_s(fd, args, s, total);
	va_end(args);
	return ((int)total);
}

static ssize_t	ft_loop_s(int fd, va_list args, const char *s, ssize_t total)
{
	ssize_t	err;
	int		i;

	i = 0;
	err = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			err = ft_parse_args(fd, s[++i], args);
			if (err == -1)
				return (err);
			total += err;
			i++;
		}
		else
		{
			err = ft_putchar_fd(s[i++], fd);
			if (err == -1)
				return (err);
			total += err;
		}
	}
	return (total);
}

static ssize_t	ft_parse_args(int fd, char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_putchar_fd((char)va_arg(args, int), fd));
	else if (specifier == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	else if (specifier == 'p')
		return (ft_putptr_fd(va_arg(args, void *), fd));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_fd(va_arg(args, int), fd));
	else if (specifier == 'u')
		return (ft_putunbr_fd(va_arg(args, unsigned int), fd));
	else if (specifier == 'x')
		return (ft_puthex_low_fd(va_arg(args, unsigned int), fd));
	else if (specifier == 'X')
		return (ft_puthex_up_fd(va_arg(args, unsigned int), fd));
	else if (specifier == '%')
		return (ft_putchar_fd('%', fd));
	return (-1);
}
