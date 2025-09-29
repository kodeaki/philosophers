/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:44:28 by tpirinen          #+#    #+#             */
/*   Updated: 2025/09/20 18:03:01 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

/*	Prints an error msg to standard error and returns an error code.		*/
int	ft_error_msg(char *err_msg, int err_code)
{
	write(2, err_msg, ft_strlen(err_msg));
	return (err_code);
}
