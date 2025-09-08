/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:18:07 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/20 18:16:42 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Allocates memory (using malloc(3)) and returns a substring from the
	string ’s’. The substring starts at index ’start’ and has a
	maximum size of ’len’.													*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	sub_len;
	size_t	j;

	if (!s)
		return (NULL);
	while (*s && start--)
		s++;
	sub_len = 0;
	while (s[sub_len] && sub_len < len)
		sub_len++;
	sub_str = malloc(sub_len + 1);
	if (!sub_str)
		return (NULL);
	j = 0;
	while (j < sub_len)
	{
		sub_str[j] = s[j];
		j++;
	}
	sub_str[sub_len] = '\0';
	return (sub_str);
}
