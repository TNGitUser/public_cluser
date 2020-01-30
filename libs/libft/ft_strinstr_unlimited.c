/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 10:49:33 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/07 16:10:17 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		cut_start(char *s, char *st)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == st[0])
		{
			j = 0;
			while (s[i] && st[j] && s[i] == st[j])
			{
				i++;
				j++;
			}
			if (st[j] == '\0')
				return (i);
			i -= j;
		}
		i++;
	}
	return (0);
}

static int		count_until_end(char *s, char *en, char *st)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_strncmp(s + i, st, ft_strlen(st)))
		{
			j++;
			i += ft_strlen(st) - 1;
		}
		else if (!ft_strncmp(s + i, en, ft_strlen(en)) && j == 0)
			return (i);
		else if (!ft_strncmp(s + i, en, ft_strlen(en)) && j >= 0)
		{
			--j;
			i += ft_strlen(en) - 1;
		}
		i++;
	}
	return (0);
}

char			*ft_strinstr_unlimited(char *s, char *st, char *en)
{
	int		i;
	int		j;
	int		k;
	char	*in;

	i = cut_start(s, st);
	j = count_until_end(s + i, en, st);
	if (i == 0 || j == 0)
		return (NULL);
	if (!(in = (char*)malloc(sizeof(char) * (j + 1))))
		return (NULL);
	k = 0;
	while (k < j)
	{
		in[k] = s[i + k];
		k++;
	}
	in[k] = 0;
	return (in);
}
