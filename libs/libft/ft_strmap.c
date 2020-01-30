/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 18:26:16 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 23:35:58 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
		mapped[i] = (*f)(s[i]);
		i++;
	}
	mapped[i] = '\0';
	return (mapped);
}
