/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 22:29:10 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 21:32:16 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1c;
	unsigned char	*s2c;
	int				k;

	s1c = (unsigned char *)s1;
	s2c = (unsigned char *)s2;
	k = 0;
	if (s1c == s2c || n == 0)
		return (0);
	while ((int)n > 0)
	{
		if (s1c[k] != s2c[k])
			return (s1c[k] - s2c[k]);
		k++;
		n--;
	}
	return (0);
}
