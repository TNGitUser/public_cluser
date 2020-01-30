/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:35:11 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/29 10:55:21 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	rcv_aux(char buffer[1024], ssize_t ssize[2], char **output
		, char *tmp)
{
	buffer[ssize[1]] = '\0';
	tmp = strjoin(*output, buffer);
	ft_memdel((void **)output);
	*output = tmp;
	ssize[0] += ssize[1];
}

static void	receive_client_aux(t_node *node, int id, int per)
{
	if (per == 100)
		node->read_err[id] = 0;
	else
	{
		if (node->read_err[id] >= 3)
		{
			printf("More than 3 read error on [%s]. Closing the client...\n"
					, node->clients[id].name);
			set_close_child(node, id);
		}
		node->read_err[id] += 1;
	}
}

char		*receive_client_string(t_node *node, int id, int *status
		, ssize_t *len)
{
	char	buffer[1025];
	char	*output;
	char	*tmp;
	ssize_t	recv;
	ssize_t	ssize[2];

	read(node->clients[id].socket, &recv, sizeof(recv));
	recv = ntohl(recv);
	if (recv == 0)
		set_close_child(node, id);
	buffer[1024] = '\0';
	output = NULL;
	tmp = NULL;
	ssize[0] = 0;
	if (recv >= 1024)
		while ((ssize[1] = read(node->clients[id].socket, buffer, 1024)) > 0)
		{
			rcv_aux(buffer, ssize, &output, tmp);
			if (ssize[0] >= recv)
				break ;
		}
	else if (recv > 0)
	{
		buffer[read(node->clients[id].socket, buffer, 1024)] = '\0';
		output = strjoin("", buffer);
		ssize[0] = strlen(output);
	}
	if (recv > 0)
		printf("Validity : %3li%%\n", ssize[0] / recv * 100);
	receive_client_aux(node, id, ssize[0] / recv * 100);
	*status = recv > 0 ? (ssize[0] / recv * 100) == 100 : 1;
	*len = recv;
	return (output);
}

char		*receive_string(t_node *node, int *status)
{
	char	buffer[1025];
	char	*output;
	char	*tmp;
	ssize_t	recv;
	ssize_t	ssize[2];

	read(node->socket_fd, &recv, sizeof(recv));
	recv = ntohl(recv);
	buffer[1024] = '\0';
	output = NULL;
	tmp = NULL;
	ssize[0] = 0;
	if (recv >= 1024)
		while ((ssize[1] = read(node->socket_fd, buffer, 1024)) > 0)
			rcv_aux(buffer, ssize, &output, tmp);
	else if (recv > 0)
	{
		buffer[read(node->socket_fd, buffer, 1024)] = '\0';
		output = strjoin("", buffer);
		ssize[0] = strlen(output);
	}
	if (recv > 0)
		printf("Validity : %3li%%\n", ssize[0] / recv * 100);
	*status = recv > 0 ? (ssize[0] / recv * 100) == 100 : 1;
	return (output);
}
