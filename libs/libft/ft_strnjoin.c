/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 14:56:40 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/30 14:56:43 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[0] = '\0';
	str = ft_strcat(str, s1);
	str = ft_strcat(str, s2);
	str = ft_strcat(str, s3);
	return (str);
}
