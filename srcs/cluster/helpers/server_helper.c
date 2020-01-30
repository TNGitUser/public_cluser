/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:04:20 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/30 13:44:37 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		server_get_active(t_node *node)
{
	int	act;
	int	i;

	i = 0;
	act = 0;
	while (i < MAXCON)
		if (node->clients[i++].active)
			++act;
	node->act = act;
	return (act);
}

int		server_get_ready(t_node *node)
{
	int	i;
	int	rdy;

	i = 0;
	rdy = 0;
	while (i < MAXCON)
	{
		if (node->clients[i].active && node->clients[i].ready)
			++rdy;
		++i;
	}
	return (rdy);
}

/*
**	Used to define the workload of each active client + server
*/

void	server_get_workload(t_node *node, int act, int wl[2], int mod[2])
{
	(void)node;
	act = act - 1;
	mod[0] = node->wh[0] % (act + 1);
	mod[1] = node->wh[1] % (act + 1);
	wl[0] = node->wh[0] / (act + 1);
	wl[1] = node->wh[1] / (act + 1);
}

void	server_set_helper(t_node *node, int i[2], char *cmd, int wl[2][2])
{
	node->bds[2] = wl[0][1] * i[1];
	node->bds[3] = wl[0][1] * (i[1] + 1) + (i[1] + 1 == node->act ? wl[1][1]
			: 0);
	cmd = get_set_cmd(1, node->clients[i[0]], node->bds);
	server_to_client(node, i[0], cmd, SET_BOUNDS);
	node->clients[i[0]].ready = 1;
	node->clients[i[0]].start[1] = node->bds[2];
	node->clients[i[0]].end[1] = node->bds[3];
	ft_memdel((void **)&cmd);
}
