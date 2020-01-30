/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:38:28 by gbianco           #+#    #+#             */
/*   Updated: 2019/06/25 05:00:20 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*retour;
	int		i;

	if (!(retour = (char *)malloc((ft_strlen(s1)) * (sizeof(char)) + 1)))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		retour[i] = s1[i];
		i++;
	}
	retour[i] = '\0';
	return (retour);
}
