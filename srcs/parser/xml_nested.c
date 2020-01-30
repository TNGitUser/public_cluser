/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_nested.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 02:27:58 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/22 21:35:11 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char	*assign_tag(char *st)
{
	char	*assign;
	int		i;
	int		len;

	len = count_tag_size(st);
	assign = (char*)ft_secmemalloc(sizeof(char) * (len + 1));
	i = -1;
	while (++(i) < len)
		assign[i] = st[i];
	assign[i] = '\0';
	return (assign);
}

static void	override_match_tags(char **next, int i)
{
	char	*closed;
	int		j;

	if (next[i] && next[i][0] != '&' && (openorclosed(next[i]) == 1))
	{
		j = 0;
		while (next[i + j + 1][0] == '&')
			j++;
		if (next[i + j + 1] && openorclosed(next[i + j + 1]) == 2)
		{
			closed = get_closed(next[i]);
			if (ft_strcmp(closed, next[i + j + 1]) != 0)
				error("Some Xml tag pair is wrong");
			ft_strdel(&closed);
			next[i][0] = '&';
			next[i + j + 1][0] = '&';
		}
	}
}

static void	none_missing_none_overlapping(int count, char **next)
{
	int	i;
	int	deep;

	deep = 1;
	while (next[0][0] != '&')
	{
		i = -1;
		while (++i < count)
			override_match_tags(next, i);
		if (deep == 1)
			equalize_deep(count, next);
		if (deep == 2)
			hardcheck_second_level(count, next);
		if (deep > MAXDEEP)
			error("Please check the nidation of all xml structure");
		deep++;
	}
}

void		check_if_correctly_nested(char *st)
{
	int		i;
	int		count;
	char	**next;

	st = st + count_tag_size(st);
	count = count_all_tags(st);
	i = 1;
	next = (char**)ft_secmemalloc(sizeof(char*) * (count + 2));
	count = 0;
	next[0] = assign_tag(st);
	while (ft_strcmp(next[count], "</scene>") != 0)
	{
		while (st[i] != '\0' && st[i] != '<')
			i++;
		if (st[i] == '\0')
			error("Problem with some xml tag");
		count++;
		next[count] = assign_tag(st + i);
		i++;
	}
	next[count + 1] = NULL;
	none_missing_none_overlapping(count, next);
	ft_strarraydel(next);
}
