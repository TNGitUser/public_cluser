/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:26:59 by gbianco           #+#    #+#             */
/*   Updated: 2019/03/04 18:05:55 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_c_l(char *ltr, char c)
{
	int		count;

	count = 0;
	while (*ltr != c && *ltr != '\0')
	{
		count++;
		ltr++;
	}
	return (count);
}

static char		*ft_trim(char *s, char c)
{
	while (*s == c && *s != '\0')
		s++;
	return (s);
}

static char		**fill_str(char **sp, char *s, char c)
{
	int i;
	int j;

	i = 0;
	while (*s != '\0')
	{
		s = ft_trim((char *)s, c);
		if (!(sp[i] = (char*)malloc((ft_c_l((char *)s, c) + 1) * sizeof(char))))
			return (0);
		j = 0;
		while (*s != c && *s != '\0')
		{
			sp[i][j++] = *s;
			s++;
		}
		sp[i][j] = '\0';
		s = ft_trim((char *)s, c);
		if (ft_strlen(sp[i]) != 0)
			i++;
	}
	sp[i] = 0;
	return (sp);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**sp;

	if (s == NULL)
		return (0);
	if (!(sp = (char**)malloc((ft_count_words((char *)s, c) + 1)
			* sizeof(char*))))
		return (0);
	sp = fill_str(sp, (char *)s, c);
	return (sp);
}
