/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:45:37 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 21:17:44 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dstc;
	unsigned char	*srcc;
	int				p;

	dstc = (unsigned char *)dst;
	srcc = (unsigned char *)src;
	p = 0;
	while (n > 0)
	{
		dstc[p] = srcc[p];
		if (srcc[p] == (unsigned char)c)
			return (dstc + p + 1);
		p++;
		n--;
	}
	return (NULL);
}
