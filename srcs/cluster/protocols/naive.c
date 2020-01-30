/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   naive.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:22:44 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/30 13:24:20 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	send_file(char *text, t_node *node, int client_fd)
{
	size_t	datalen;
	size_t	to_send;
	char	buffer[129];
	size_t	i;

	(void)node;
	datalen = strlen(text);
	to_send = htonl(datalen);
	printf("File size : %li\n", datalen);
	send(client_fd, &to_send, sizeof(to_send), 0);
	if (datalen > 128)
	{
		i = 0;
		while (i < datalen)
		{
			buffer[128] = '\0';
			strncpy(buffer, text + i, 128);
			send(client_fd, &buffer, strlen(buffer), 0);
			i += 128;
		}
	}
	else
		send(client_fd, &text, datalen, 0);
	sleep(1);
}

void	receive_client_file(t_node *node, int fd, int id, ssize_t *len)
{
	size_t	recv_t;
	size_t	rsize[2];
	char	*data;
	char	buffer[128 + 1];
	char	*output;

	printf("Awaiting file from %i\n", fd);
	recv(fd, &recv_t, sizeof(recv_t), 0);
	recv_t = ntohl(recv_t);
	printf("Expected size : %li\n", recv_t);
	rsize[0] = 0;
	data = strdup("");
	while ((rsize[1] = recv(fd, buffer, 128, 0)) > 0)
	{
		rsize[0] += rsize[1];
		buffer[rsize[1]] = '\0';
		output = strjoin(data, buffer);
		free(data);
		data = output;
		//printf("Current : %li\n", rsize[0]);
		if (rsize[0] >= recv_t)
			break ;
	}
	*len = recv_t;
	printf("Integrity : %li%%\n", rsize[0] / recv_t * 100);
	node->computed_scene[id] = output;
}

void	receive_file(t_node *node)
{
	size_t	recv;
	size_t	rsize[2];
	char	*data;
	char	buffer[128 + 1];
	char	*output;

	printf("Awaiting file\n");
	read(node->socket_fd, &recv, sizeof(recv));
	recv = ntohl(recv);
	printf("Expected size : %li\n", recv);
	rsize[0] = 0;
	data = strdup("");
	while ((rsize[1] = read(node->socket_fd, buffer, 128)) > 0)
	{
		rsize[0] += rsize[1];
		buffer[rsize[1]] = '\0';
		output = strjoin(data, buffer);
		free(data);
		data = output;
		printf("Current : %li\n", rsize[0]);
		if (rsize[0] >= recv)
			break ;
	}
	printf("Integrity : %li%%\n", rsize[0] / recv * 100);
	node->param = output;
}
