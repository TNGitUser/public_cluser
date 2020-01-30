/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:23:09 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/28 16:35:43 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	set_get_protocol(char *cmd)
{
	int					prot;
	int					i;
	static const char	*directives[] = { "CLIENT", "BOUNDS", NULL };

	prot = -1;
	i = 0;
	while (directives[i])
	{
		if (ft_strstr(cmd, directives[i]))
		{
			if (prot != -1)
				return (-1);
			prot = i;
		}
		++i;
	}
	return (prot);
}

static int	set_client(t_node *node, char *cmd)
{
	char	*name;

	cmd = ft_strstr(cmd, "CLIENT");
	if (!cmd)
		error("CRITICAL ERROR : set_client failed");
	while (*cmd && *cmd != '\'')
		++cmd;
	if (!cmd || *(cmd) != '\'')
	{
		printf("Error, wrong data format for 'SET CLIENT' command\n");
		return (-1);
	}
	if (!(name = extract_string(&cmd, '\'', '\'')))
		error("CRITICAL ERROR : set_client failed, name retrieval failed");
	node->info.name = name;
	while (*cmd && *cmd != '[')
		++cmd;
	if (!cmd || *cmd != '[')
		printf("Error, wrong color format for 'SET CLIENT' command\n");
	else
		string_to_color(cmd, node);
	return (0);
}

static int	set_bounds(t_node *node, char *cmd)
{
	int		i;
	t_scene *s;

	s = (t_scene *)node->s_ptr;
	i = 0;
	if (!(cmd = ft_strstr(cmd, "BOUNDS")))
		error("CRITICAL ERROR : set_bounds failed");
	while (i < 4)
	{
		while (*cmd && *cmd != ' ')
			++cmd;
		++cmd;
		if (i < 2)
			node->info.start[i] = ft_atoi(cmd);
		else
			node->info.end[i - 2] = ft_atoi(cmd);
		++i;
	}
	s->min_y = node->info.end[0];
	s->max_y = node->info.end[1];
	node->info.ready = 1;
	return (0);
}

int			cmd_set(t_node *node, char *cmd)
{
	int	prot;

	prot = set_get_protocol(cmd);
	if (prot == -1)
		error("ERROR, unknown or bad formatted protocol");
	if (prot == 0)
		set_client(node, cmd);
	else if (prot == 1)
		set_bounds(node, cmd);
	else
		printf("Not implemented yet\n");
	printf("Client name : '%s'\n", node->info.name);
	printf("Client color : (%.3i,%.3i,%.3i)\n", node->info.color[0]
			, node->info.color[1], node->info.color[2]);
	printf("Client bounds : (%i,%i) & (%i,%i)\n", node->info.start[0]
			, node->info.start[1], node->info.end[0], node->info.end[1]);
	return (0);
}
