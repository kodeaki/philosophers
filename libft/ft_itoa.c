/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:19:53 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/03 18:01:17 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_len(int n);

/*	Allocates memory (using malloc(3)) and returns a string representing
	the integer received as an argument. Negative numbers are handled.		*/
char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	size_t	len;
	size_t	start_index;

	len = ft_count_len(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	num = n;
	str[len] = '\0';
	start_index = 0;
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
		start_index = 1;
	}
	while (len-- > start_index)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

static size_t	ft_count_len(int n)
{
	size_t	len;
	long	num;

	num = n;
	len = (n <= 0);
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}
