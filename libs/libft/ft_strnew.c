/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:03:25 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 22:06:17 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new;
	int		i;

	if (!(new = (char *)malloc(size + 1 * sizeof(char))))
		return (NULL);
	i = 0;
	while (i <= (int)size)
	{
		new[i] = '\0';
		i++;
	}
	return (new);
}
