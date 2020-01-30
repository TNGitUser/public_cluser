/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:22:36 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/28 11:24:38 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			cmd_dispatch(t_node *node, char *cmd, int *status)
{
	if (*status == 0)
		return (cmd_set(node, cmd));
	else if (*status == 1)
		return (cmd_status(node, cmd));
	else if (*status == 2)
		return (cmd_run(node, cmd));
	else if (*status == 3)
		return (cmd_return(node, cmd));
	else if (*status == 4)
		return (cmd_close(node, cmd));
	return (-1);
}

int			is_command(char *cmd, int *prot)
{
	int					i;
	static const char	*directives[] = { "SET", "STATUS", "RUN", "RETURN"
		, "CLOSE", NULL};

	i = 0;
	while (directives[i])
	{
		if (!ft_strncmp(cmd, directives[i], ft_strlen(directives[i])))
		{
			*prot = i;
			return (1);
		}
		++i;
	}
	return (0);
}

static char	*get_cmd_bounds(int bounds[4])
{
	char	*tmp;
	char	*output;
	char	*bounds_c[4];

	bounds_c[0] = ft_itoa(bounds[0]);
	bounds_c[1] = ft_itoa(bounds[1]);
	bounds_c[2] = ft_itoa(bounds[2]);
	bounds_c[3] = ft_itoa(bounds[3]);
	tmp = ft_strnjoin(bounds_c[0], " ", bounds_c[1]);
	ft_memdel((void **)&bounds_c[0]);
	ft_memdel((void **)&bounds_c[1]);
	output = ft_strnjoin(tmp, " ", bounds_c[2]);
	ft_memdel((void **)&bounds_c[2]);
	ft_memdel((void **)&tmp);
	tmp = ft_strnjoin(output, " ", bounds_c[3]);
	ft_memdel((void **)&output);
	ft_memdel((void **)&bounds_c[3]);
	if (!tmp)
		error("Failed to convert bounds to string");
	return (tmp);
}

char		*get_set_cmd(int cmd_t, t_client client, int bounds[4])
{
	char	*tmp;
	char	*output;
	char	*color;

	output = NULL;
	if (cmd_t == 0)
	{
		tmp = strnjoin("SET CLIENT '", client.name, "'");
		color = color_to_string(client.color);
		output = strnjoin(tmp, " ", color);
		ft_memdel((void **)&tmp);
		ft_memdel((void **)&color);
	}
	else if (cmd_t == 1 && bounds)
	{
		tmp = get_cmd_bounds(bounds);
		output = strjoin("SET BOUNDS ", tmp);
		ft_memdel((void **)&tmp);
	}
	else
		error("Unknown protocol for get_set_cmd");
	return (output);
}

char		*get_other_cmd(int cmd_t, t_node *node)
{
	char	*output;

	(void)node;
	output = NULL;
	if (cmd_t == SEND_SCENE)
		output = ft_strdup("RUN");
	else if (cmd_t == ASK_STATUS)
		output = ft_strdup("STATUS");
	else if (cmd_t == GET_SCENE)
		output = ft_strdup("RETURN");
	else if (cmd_t == CLOSE_CLIENT)
		output = ft_strdup("CLOSE");
	else
		error("Unknown command protocol");
	return (output);
}
