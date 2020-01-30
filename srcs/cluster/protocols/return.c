/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:22:57 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/30 13:28:15 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	cmd_return(t_node *node, char *cmd)
{
	(void)node;
	(void)cmd;
	printf("This function should return the completed image to the server\n");
	//send_string(node->socket_fd, node, "RETURN");
	sleep(1);
	send_image(node->socket_fd, node);
	return (0);
}
