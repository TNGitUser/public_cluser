/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:23:01 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/28 15:01:18 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	CLUSTER : if this function is reached, RT should perform its part
*/

int	cmd_run(t_node *node, char *cmd)
{
	t_scene *s;

	(void)cmd;
	s = (t_scene *)node->s_ptr;
	if (!s)
		error("Scene pointer failed us. Aborting...");
	receive_file(node);
	if (!node->param)
		error("Corrupted input. Aborting...");
	parse(s, 0, 0, node->param);
	node->exec = 1;
	return (0);
}
