/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_equality.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 02:27:51 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/13 11:18:20 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	equalize_effects(int count, char **next, int *i)
{
	while (ft_strcmp(next[*i], "</effects>") != 0)
	{
		(*i)++;
		if (*i > count + 1)
			error("Tag nidation error");
		if (ft_strcmp(next[*i], "<anaglyph>") == 0)
			next[*i][0] = '&';
		if (ft_strcmp(next[*i], "</anaglyph>") == 0)
			next[*i][0] = '&';
		if (ft_strcmp(next[*i], "<globalblur>") == 0)
			next[*i][0] = '&';
		if (ft_strcmp(next[*i], "</globalblur>") == 0)
			next[*i][0] = '&';
	}
}

static void	equalize_group(int count, char **next, int *i)
{
	while (ft_strcmp(next[*i], "</mesh>") != 0)
	{
		(*i)++;
		if (*i > count + 1)
			error("Tag nidation error");
		if (ft_strcmp(next[*i], "<part>") == 0)
		{
			next[*i][0] = '&';
			while (ft_strcmp(next[*i], "</part>") != 0)
			{
				(*i)++;
				if (*i > count + 1)
					error("Tag nidation error");
				if (ft_strcmp(next[*i], "<part>") == 0)
					error("Part tag nidation error");
			}
			next[*i][0] = '&';
		}
	}
}

void		equalize_deep(int count, char **next)
{
	int		i;

	i = -1;
	while (++i < count + 1)
	{
		if (ft_strcmp(next[i], "<effects>") == 0)
			equalize_effects(count, next, &i);
		if (ft_strcmp(next[i], "<mesh>") == 0)
			equalize_group(count, next, &i);
	}
}

void		hardcheck_second_level(int count, char **next)
{
	char	*str[6];
	int		i;
	int		j;

	str[0] = "<camera>";
	str[1] = "<window>";
	str[2] = "<effects>";
	str[3] = "<light>";
	str[4] = "<object>";
	str[5] = "<mesh>";
	j = -1;
	while (++j < count + 1)
	{
		if (next[j][0] != '&')
		{
			i = -1;
			while (++i < 6)
				if (ft_strcmp(next[j], str[i]) == 0)
					error("Principal block nesting problem found");
		}
	}
}
