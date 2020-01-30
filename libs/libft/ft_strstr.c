/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:38:35 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/12 18:14:15 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	j = ft_strlen(needle);
	if (j == 0)
		return ((void *)haystack);
	while (haystack[i] != '\0' && needle[k] != '\0')
	{
		while (haystack[i + k] == needle[k] && haystack[i + k] != '\0'
				&& needle[k] != '\0')
		{
			k++;
			if (k == j)
			{
				return ((void *)haystack + i);
			}
		}
		k = 0;
		i++;
	}
	return (NULL);
}
