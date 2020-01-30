/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:37:42 by gbianco           #+#    #+#             */
/*   Updated: 2018/12/11 15:00:48 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*section;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (!(section = (char *)malloc(len * sizeof(char) + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		section[i] = s[start + i];
		i++;
	}
	section[i] = '\0';
	return (section);
}
