/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:35:57 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/22 02:38:17 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_int_buffer(long nb)
{
	int			buffer;
	int			neg;

	buffer = 0;
	neg = 0;
	if (nb <= 0)
		neg++;
	while (nb)
	{
		nb = nb / 10;
		buffer++;
	}
	return (buffer + neg);
}
