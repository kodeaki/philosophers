/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:30:46 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/03 17:56:47 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Applies the function 'f' to each character of the string 's', passing its
	index as the first argument and the character itself as the second.
	A new string is created (using malloc(3)) to store the results from
	the successive applications of 'f'.										*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_s;
	size_t	s_len;
	size_t	i;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	new_s = (char *)malloc(s_len + 1);
	if (!new_s)
		return (NULL);
	new_s[s_len] = '\0';
	i = 0;
	while (i < s_len)
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	return (new_s);
}
