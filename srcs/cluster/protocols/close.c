/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:22:05 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/28 11:22:06 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	cmd_close(t_node *node, char *cmd)
{
	(void)node;
	(void)cmd;
	printf("You were asked to be close\n");
	close(node->socket_fd);
	node->info.active = 0;
	ft_memdel((void **)&node->info.name);
	ft_memdel((void **)&node->param);
	return (0);
}
