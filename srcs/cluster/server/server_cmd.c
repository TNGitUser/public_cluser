/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:04:13 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/30 13:37:52 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	cmd_is_srv_cmd(char *cmd)
{
	int					i;
	static const char	*directives[] = { "SET", "STATUS", "RUN", "LOCK"
		, "UNLOCK", NULL};

	i = 0;
	while (directives[i])
	{
		if (!ft_strncmp(cmd, directives[i], ft_strlen(directives[i])))
		{
			return (i);
		}
		++i;
	}
	return (-1);
}

static int	server_status(t_node *node, char *cmd)
{
	int		i;
	char	*err;

	err = "Error, STATUS command is not correctly formated. Expecting 'STATUS'";
	if (!(cmd = ft_strstr(cmd, "STATUS")) || *(cmd + 6) != '\0')
		return (nerror(err));
	i = 0;
	printf("Lock Status : %s\033[0m\n", node->lock ? "\033[32mON"
			: "\033[31mOFF");
	while (i < MAXCON)
	{
		if (node->clients[i].active)
			printf("Client %i : [%s] \033[32mActive\033[0m, socket : %i\n"
					, i, node->clients[i].name, node->clients[i].socket);
		else
			printf("Client %i : \033[31mInactive\033[0m\n", i);
		++i;
	}
	return (0);
}

static void	server_get_image(t_node *node)
{
	pthread_t	courier[MAXCON];
	t_ret		ret[MAXCON];
	int			i;

	i = 0;
	while (i < MAXCON)
	{
		ret[i].node = node;
		ret[i].cl_id = i;
		if (node->clients[i].active)
		{
			pthread_create(&courier[i], NULL, server_get, &ret[i]);
			node->clients[i].ready = 0;
			node->clients[i].set = 0;
		}
		++i;
	}
	i = 0;
	while (i < MAXCON)
	{
		if (node->clients[i].active)
			pthread_join(courier[i], NULL);
		++i;
	}
	server_init_mlx(node->s_ptr);
	server_assemble(node->s_ptr);
	server_loop_mlx(node->s_ptr);
}

static int	server_runn(t_node *node)
{
	char	*data;
	int		i;
	char	*cmd;

	if (!node->lock)
		printf("Server need to be LOCK to use RUN");
	if (!server_get_ready(node))
		return (nerror("No client are ready ! Aborting..."));
	data = get_data_filename(node->param);
	i = 0;
	cmd = get_other_cmd(SEND_SCENE, node);
	while (i < MAXCON)
	{
		if (node->clients[i].active)
		{
			server_to_client(node, i, cmd, SEND_SCENE);
			send_file(data, node, node->clients[i].socket);
		}
		++i;
	}
	server_get_image(node);
	node->lock = 0;
	ft_memdel((void **)&data);
	return (0);
}

/*
**	Function will be used to set workload of each child
*/

static int	server_set(t_node *node)
{
	int		act;
	int		wl[2][2];
	int		i[2];
	char	*cmd_bds;

	if (!node->lock)
		return (nerror("Server need to be LOCK to use SET"));
	if ((act = server_get_active(node)) <= 0)
		return (nerror("No client. Aborting operation..."));
	server_get_workload(node, act, wl[0], wl[1]);
	i[1] = 0;
	i[0] = -1;
	node->bds[0] = 0;
	node->bds[1] = node->wh[0];
	act = server_get_active(node);
	cmd_bds = NULL;
	while (++i[0] < MAXCON)
		if (node->clients[i[0]].active)
		{
			server_set_helper(node, i, cmd_bds, wl);
			++i[1];
		}
	return (0);
}

/*
**	TODO : See to use more thread to be faster on the cmd sending
*/

int			server_dispatch(t_node *node, char *cmd)
{
	int		cmd_t;
	char	*error;

	error = "Unknown server command : use [SET, STATUS, RUN, LOCK, UNLOCK]";
	if ((cmd_t = cmd_is_srv_cmd(cmd)) == -1 || cmd_t > 4)
		return (nerror(error));
	if (cmd_t == 0)
		return (server_set(node));
	else if (cmd_t == 1)
		return (server_status(node, cmd));
	else if (cmd_t == 2)
		return (server_runn(node));
	else if (cmd_t == 3 || cmd_t == 4)
		node->lock = cmd_t == 3 ? 1 : 0;
	return (0);
}
