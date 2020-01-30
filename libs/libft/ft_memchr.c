/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 22:07:26 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 21:30:16 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*sc;

	sc = (char *)s;
	while (n > 0)
	{
		if (*sc == ((char)c))
			return (sc);
		sc++;
		n--;
	}
	return (NULL);
}
