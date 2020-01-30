/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 02:28:07 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/12 02:28:10 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int			openorclosed(char *st)
{
	int i;

	i = 0;
	while (st[0] != '\0' && st[0] != '&' && st[0] != '<')
		i++;
	if (st[i] != '\0' && st[i] == '<' && st[i + 1] != '/')
	{
		while (st[i] != '\0' && st[i] != '>')
			i++;
		if (st[i] == '>')
			return (1);
	}
	else if (st[i] != '\0' && st[i] == '<' && st[i + 1] == '/')
	{
		while (st[i] != '\0' && st[i] != '>')
			i++;
		if (st[i] == '>')
			return (2);
	}
	return (0);
}

char		*get_closed(char *open)
{
	char	*closed;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(open);
	closed = (char*)ft_secmemalloc(sizeof(char) * (len + 2));
	closed[0] = open[0];
	closed[1] = '/';
	i = 1;
	j = 2;
	while (i < len)
	{
		closed[j] = open[i];
		i++;
		j++;
	}
	closed[j] = '\0';
	return (closed);
}

static int	check_header(char *str)
{
	int		i;
	int		j;
	char	*header;

	i = count_tag_size(str);
	header = (char*)ft_secmemalloc(sizeof(char) * (i + 1));
	j = 0;
	while (j < i)
	{
		header[j] = str[j];
		j++;
	}
	header[j] = '\0';
	if (ft_strcmp(header, "<?xml version=\"1.0\" encoding=\"ASCII\"?>") != 0)
		error("The xml header is not valid");
	ft_strdel(&header);
	return (i);
}

static void	check_forbidden_characters(char c)
{
	if (c < 45 || c > 122)
		error("Forbidden xml character detected");
	if (ft_isascii(c) == 0)
		error("Forbidden xml character detected");
	if (c > 90 && c < 95)
		error("Forbidden xml character detected");
	if (c == '@' || c == '`')
		error("Forbidden xml character detected");
	if (c == ';' || c == '<' || c == '=' || c == '?')
		error("Forbidden xml character detected");
}

void		check_xml_validity(char *st)
{
	int i;

	i = check_header(st) - 1;
	while (st[++i] != '\0')
	{
		if (st[i] != '\0' && st[i] == '&')
			error("Forbidden xml character detected");
		if (st[i] != '\0' && st[i] == '<' && st[i + 1] != '/')
			if (st[i + 1] != '\0' && ft_iscapital(st[i + 1]) == 0)
				error("Xml tags can't start with capitals letters");
		if (st[i] != '\0' && st[i] == '<')
			while (st[i] != '\0' && st[i] != '>')
			{
				i++;
				check_forbidden_characters(st[i]);
			}
		if (st[i] == '\0')
			error("Problem with some xml tag");
	}
	check_if_correctly_nested(st);
}
