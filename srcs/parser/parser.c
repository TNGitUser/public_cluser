/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:24:45 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/28 14:12:01 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	valid_chars(char *str)
{
	int	i;
	int	ct;

	i = -1;
	ct = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '<')
		{
			while (str[i] != '\0' && str[i] != '>')
			{
				i++;
				ct++;
			}
		}
		if (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			ct++;
		if (str[i] == '\0')
			break ;
	}
	return (ct);
}

static char	*clean_spaces_tabs_nlines(char *st)
{
	char	*new;
	int		i;
	int		j;

	new = (char*)ft_secmemalloc(sizeof(char) * (valid_chars(st) + 1));
	i = -1;
	j = 0;
	while (st[++i] != '\0')
	{
		if (st[i] == '<')
			while (st[i] != '\0' && st[i] != '>')
				new[j++] = st[i++];
		if (st[i] != '\0' && st[i] != ' ' && st[i] != '\t' && st[i] != '\n')
			new[j++] = st[i];
		if (st[i] == '\0')
			error("Problem with some xml tag");
	}
	new[j] = '\0';
	return (new);
}

static char	*read_file(int fd, char *str)
{
	char	*temp;
	char	*st;
	int		rd;

	st = (char*)ft_secmemalloc(1);
	st[0] = '\0';
	rd = BUFF_SIZE;
	while (rd == BUFF_SIZE)
	{
		if ((rd = read(fd, str, BUFF_SIZE)) == -1)
			error("Error opening the file");
		if (str[0] == '\0')
			error("Invalid file");
		str[rd] = '\0';
		temp = st;
		st = ft_strjoin(st, str);
		ft_strdel(&temp);
	}
	ft_strdel(&str);
	return (st);
}

static void	check_file_extension(char *av)
{
	char	*xml;
	int		i;
	int		j;

	xml = ".xml";
	i = ft_strlen(av) - 4;
	j = 0;
	while (av[i] != '\0')
	{
		if (xml[j] && av[i] != xml[j])
			error("The file extension is not [.xml]");
		i++;
		j++;
	}
}

void		parse(t_scene *s, char *av, int *ac, char *data)
{
	char	*str;
	char	*new;
	int		fd;

	(void)ac;
	if (!data)
		check_file_extension(av);
	if (!data && (fd = open(av, O_RDONLY)) < 0)
		error("Error reading the file, sure that it exists?");
	if (data == NULL)
	{
		str = (char*)ft_secmemalloc(sizeof(char) * (BUFF_SIZE + 1));
		str = read_file(fd, str);
	}
	else
		str = data;
	new = clean_spaces_tabs_nlines(str);
	ft_strdel(&str);
	check_xml_validity(new);
	count_tags(s, new);
	split_all_tags(s, new);
}
