/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:41:23 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/03 18:45:56 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Returns a pointer to a new string which is a duplicate of the string 's'.
	Memory for the new string is obtained with malloc(3), and can be freed
	with free(3)															*/
char	*ft_strdup(const char *s)
{
	return (ft_substr(s, 0, ft_strlen(s)));
}
