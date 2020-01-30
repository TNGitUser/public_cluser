/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:45:17 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 15:49:12 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*s1c;
	unsigned char	*s2c;

	s1c = (unsigned char*)s1;
	s2c = (unsigned char*)s2;
	i = 0;
	while ((s1c[i] != '\0' || s2c[i] != '\0') && n > 0)
	{
		if (s1c[i] != s2c[i])
			return (s1c[i] - s2c[i]);
		i++;
		n--;
	}
	return (0);
}
