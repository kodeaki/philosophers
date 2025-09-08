/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:10:38 by tpirinen          #+#    #+#             */
/*   Updated: 2025/05/03 18:06:29 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Count the number of nodes in the list.									*/
int	ft_lstsize(t_list *lst)
{
	t_list	*iter;
	int		lstsize;

	if (!lst)
		return (0);
	iter = lst;
	lstsize = 0;
	while (iter)
	{
		iter = iter->next;
		lstsize++;
	}
	return (lstsize);
}
