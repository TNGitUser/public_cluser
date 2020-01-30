/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:52:37 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/28 15:52:22 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	client_connect(int socket_fd, struct sockaddr *serv_addr
		, size_t addr_len)
{
	if (connect(socket_fd, serv_addr, addr_len) > 0)
		error("Connection failed");
}

static void	client_init_info(t_node *node)
{
	t_client	*info;

	info = &(node->info);
	info->name = NULL;
	ft_bzero(info->start, sizeof(int) * 2);
	ft_bzero(info->end, sizeof(int) * 2);
	ft_bzero(info->color, sizeof(int) * 3);
	info->ready = 0;
	info->set = 0;
	info->active = 1;
}

void		init_client(t_node *node, char *server_address)
{
	int					socket_fd;
	struct sockaddr_in	serv_addr;

	socket_fd = -1;
	socket_fd = socket_init();
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, server_address, &serv_addr.sin_addr) <= 0)
		error("Invalid address / Error while converting address to binary");
	client_connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	node->addr = serv_addr;
	node->socket_fd = socket_fd;
	node->type = CLIENT;
	node->err = 0;
	node->exec = 0;
	node->info.file_data = NULL;
	node->info.set = 0;
	node->info.ready = 0;
	client_init_info(node);
}
