/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:05:39 by gbianco           #+#    #+#             */
/*   Updated: 2019/06/27 12:07:28 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int				p;
	char			*s1;
	char			*s2;

	s1 = (char *)dst;
	s2 = (char *)src;
	p = 0;
	while (n > 0)
	{
		s1[p] = s2[p];
		p++;
		n--;
	}
	return (dst);
}
