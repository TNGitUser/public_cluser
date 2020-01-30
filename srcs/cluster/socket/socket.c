/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:52:34 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/29 14:16:24 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			socket_init(void)
{
	int socket_fd;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == 0)
		error("Socket creation failed");
	return (socket_fd);
}

static void	socket_setopt(int socket_fd, struct sockaddr_in *address)
{
	int	opt;

	opt = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt
				, sizeof(opt)))
		error("Socket option binding failed");
	address->sin_family = AF_INET;
	address->sin_addr.s_addr = INADDR_ANY;
	address->sin_port = htons(PORT);
}

static void	socket_bind(int socket_fd, struct sockaddr_in *address)
{
	if (bind(socket_fd, (struct sockaddr *)address, sizeof(*address)) < 0)
		error("Socket bind failed");
	if (listen(socket_fd, MAXCON) < 0)
		error("Socket listening failed");
}

static void	socket_client_init(t_node *node)
{
	int	client;

	client = -1;
	while (++client < MAXCON)
	{
		node->con_socket[client] = 0;
		node->read_err[client] = 0;
		node->computed_scene[client] = NULL;
		node->computed[client] = 0;
	}
}

void		init_server(t_node *node)
{
	int					socket_fd;
	struct sockaddr_in	address;
	int					i;

	srand(time(NULL));
	socket_fd = -1;
	socket_fd = socket_init();
	socket_setopt(socket_fd, &address);
	socket_bind(socket_fd, &address);
	socket_client_init(node);
	node->addr = address;
	node->serv_addr = address;
	node->socket_fd = socket_fd;
	node->type = SERVER;
	node->err = 0;
	node->lock = 0;
	i = 0;
	while (i < MAXCON)
		node->clients[i++].active = 0;
	get_name_file(node);
}
