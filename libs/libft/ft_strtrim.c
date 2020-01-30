/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 21:53:41 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 22:47:05 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		start;
	char	*trimmed;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	start = i;
	j = ft_strlen(s) - 1;
	while ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t') && s[i] != '\0')
	{
		i++;
		j--;
	}
	if (!(trimmed = (char *)malloc((ft_strlen(s) - i + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (start + (++i) <= j)
		trimmed[i] = s[start + i];
	trimmed[i] = '\0';
	return (trimmed);
}
