/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:22:12 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/28 15:54:14 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	Send command
**	Wait for confirmation | WARNING : Not implemented yet
*/

int		server_send(t_node *node, int client_fd, char *cmd)
{
	send_string(client_fd, node, cmd);
	return (0);
}

void	server_to_client(t_node *node, int client_id, char *cmd, int prot)
{
	char	*data;

	if (prot == SET_CLIENT)
		server_send(node, node->clients[client_id].socket, cmd);
	else if (prot == SET_BOUNDS)
		server_send(node, node->clients[client_id].socket, cmd);
	else if (prot == SEND_SCENE)
	{
		server_send(node, node->clients[client_id].socket, cmd);
		data = get_data_filename(node->param);
		send_file(data, node, node->clients[client_id].socket);
		ft_memdel((void **)&data);
	}
	else if (prot == GET_SCENE)
		server_send(node, node->clients[client_id].socket, cmd);
	else if (prot == CLOSE_CLIENT)
		server_send(node, node->clients[client_id].socket, cmd);
	else
		printf("\033[32mUnknown command\033[0m\n");
}

void	await_command(t_node *node)
{
	int		status;
	char	*cmd;

	cmd = receive_string(node, &status);
	if (!status || !cmd)
	{
		if (node->err++ >= 3)
			error("Too many NULL received. Aborting...");
		printf("Error : received failed\n");
		ft_memdel((void **)&cmd);
		return ;
	}
	if (!is_command(cmd, &status))
	{
		printf("Error : unkown command\n[%s]\n", cmd);
		return ;
	}
	cmd_dispatch(node, cmd, &status);
	ft_memdel((void **)&cmd);
}
