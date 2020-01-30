/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:52:25 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/28 10:53:06 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_name_base(t_node *node, char *text)
{
	size_t	name_count;
	size_t	id;
	char	*name;

	name_count = strocc(text, '\n');
	if (name_count == 0)
		return ;
	if (!(node->namebase.names = malloc(sizeof(char *) * (name_count + 1))))
		error("Failed to malloc name base");
	id = 0;
	node->namebase.count = name_count;
	node->namebase.names[name_count] = NULL;
	while (*text)
	{
		name = strdelim(&text, '\n');
		node->namebase.names[id++] = name;
		if (!(*text))
			break ;
		if (*text == '\n')
			++text;
	}
}

void		get_name_file(t_node *node)
{
	char	*text;

	if (access(NAME_BASE, F_OK))
		return ;
	text = get_data_filename(NAME_BASE);
	set_name_base(node, text);
	if (text)
		free(text);
}

void		get_client_name(t_node *node, int id)
{
	size_t	name_id;

	name_id = rand() % (node->namebase.count);
	node->clients[id].name = node->namebase.names[name_id];
	node->clients[id].name_id = name_id;
	node->clients[id].color[0] = rand() % 256;
	node->clients[id].color[1] = rand() % 256;
	node->clients[id].color[2] = rand() % 256;
}
