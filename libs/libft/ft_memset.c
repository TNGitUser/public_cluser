/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:30:40 by gbianco           #+#    #+#             */
/*   Updated: 2019/02/21 21:48:20 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bc;
	unsigned char	cc;
	int				i;

	bc = (unsigned char *)b;
	cc = (unsigned char)c;
	i = 0;
	while (len > 0)
	{
		bc[i] = cc;
		len--;
		i++;
	}
	return (b);
}
