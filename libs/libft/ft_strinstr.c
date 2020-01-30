/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 10:49:33 by gbianco           #+#    #+#             */
/*   Updated: 2019/11/18 16:47:08 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static int		count_until_end(char *s, char *en)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == en[j])
		{
			while (s[i] && en[j] && s[i] == en[j])
			{
				i++;
				j++;
				if (en[j] == '\0')
					return (i - j);
			}
			i -= j;
			j = 0;
		}
		i++;
	}
	return (0);
}

char			*ft_strinstr(char *s, char *st, char *en)
{
	int		i;
	int		j;
	int		k;
	char	*in;

	i = cut_start(s, st);
	j = count_until_end(s + i, en);
	if (i == 0 || j == 0)
		return (NULL);
	if (!(in = (char*)malloc(sizeof(char) * (j + 1))))
		return (NULL);
	k = 0;
	while (i + k < i + j)
	{
		in[k] = s[i + k];
		k++;
	}
	in[k] = 0;
	return (in);
}
