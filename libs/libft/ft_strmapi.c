/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:03:41 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 23:44:44 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mapped;
	int		i;

	if (s == NULL)
		return (NULL);
	if (!(mapped = (char *)malloc(ft_strlen(s) + 1 * sizeof(char))))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		mapped[i] = (*f)(i, s[i]);
		i++;
	}
	mapped[i] = '\0';
	return (mapped);
}
