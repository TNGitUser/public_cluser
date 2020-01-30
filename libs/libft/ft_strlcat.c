/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:43:30 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/20 05:30:04 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int buff;
	int rtrn;
	int i;
	int j;

	i = 0;
	j = 0;
	if ((ft_strlen(dst) + 1) <= size)
		rtrn = (ft_strlen(dst) + ft_strlen(src));
	else
		rtrn = (ft_strlen(src) + size);
	buff = size - 1;
	while (dst[i] != '\0')
		i++;
	while (i < buff && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (rtrn);
}
