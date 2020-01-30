/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:41:29 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/20 03:12:34 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dstc;
	char		*srcc;
	size_t		i;

	dstc = (char *)dst;
	srcc = (char *)src;
	if (srcc >= dstc)
	{
		i = 0;
		while (i < len)
		{
			dstc[i] = srcc[i];
			i++;
		}
	}
	else
	{
		i = len - 1;
		while ((int)i >= 0)
		{
			dstc[i] = srcc[i];
			i--;
		}
	}
	return (dst);
}
