/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:14:24 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 18:54:38 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	*s1c;
	unsigned char	*s2c;

	s1c = (unsigned char*)s1;
	s2c = (unsigned char*)s2;
	i = 0;
	while (s1c[i] != '\0' || s2c[i] != '\0')
	{
		if (s1c[i] != s2c[i])
			return (s1c[i] - s2c[i]);
		i++;
	}
	return (0);
}
