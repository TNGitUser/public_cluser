/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:18:30 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/12 18:13:44 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	j = ft_strlen(needle);
	if (j == 0)
		return ((void *)haystack);
	while (haystack[i] != '\0' && needle[k] != '\0' && i < len)
	{
		while (haystack[i + k] == needle[k] && haystack[i + k] != '\0'
				&& needle[k] != '\0' && (i + k) < len)
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
