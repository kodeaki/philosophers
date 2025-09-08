/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:45:33 by tpirinen          #+#    #+#             */
/*   Updated: 2025/06/10 21:38:03 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	ft_parse_args(char specifier, va_list args);
static ssize_t	ft_loop_s(va_list args, const char *s, ssize_t err);

int	ft_printf(const char *s, ...)
{
	va_list	args;
	ssize_t	chars_printed;

	if (!s)
		return (-1);
	chars_printed = 0;
	va_start(args, s);
	chars_printed = ft_loop_s(args, s, chars_printed);
	va_end(args);
	return ((int)chars_printed);
}

static ssize_t	ft_loop_s(va_list args, const char *s, ssize_t chars_printed)
{
	ssize_t	err;
	int		i;

	i = 0;
	err = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			err = ft_parse_args(s[++i], args);
			if (err == -1)
				return (err);
			chars_printed += err;
			i++;
		}
		else
		{
			err = ft_putchar_fd(s[i++], 1);
			if (err == -1)
				return (err);
			chars_printed += err;
		}
	}
	return (chars_printed);
}

static ssize_t	ft_parse_args(char specifier, va_list args)
{
	int			fd;

	fd = 1;
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
