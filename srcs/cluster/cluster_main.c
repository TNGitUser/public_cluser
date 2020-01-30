/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cluster_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:40:50 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/29 15:50:40 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		cluster(t_scene *s, char *file)
{
	t_node	*node;

	node = &(s[0].info);
	node->s_ptr = (void *)(&s[0]);
	init_server(node);
	node->wh[0] = s[0].mlx.wid;
	node->wh[1] = s[0].mlx.hei;
	printf("Scene dimsensions  :\n\t- Width : %i\n\t- Height : %i\n\n"
			, s[0].mlx.wid, s[0].mlx.hei);
	node->param = file;
	server_run(node);
	return ;
}

static void	get_client_info(t_node *node)
{
	char	*input;

	input = NULL;
	printf("Please input target ip : \n");
	/*if (get_next_line(STDIN_FILENO, &input) < 0 || !input || input[0] == '\0')
		error("Failed to retrieve input on STDIN");*/
	input = "0.0.0.0";
	if (is_ip_valid(input))
		init_client(node, input);
	else
	{
		printf("\033[0;31mError, IP is invalid\033[0m\n");
		get_client_info(node);
	}
}

void		cluster_client(t_scene *s)
{
	t_node *node;

	node = &(s[0].info);
	node->s_ptr = (void *)(&s[0]);
	get_client_info(node);
	while(!node->exec)
		await_command(node);
	return ;
}
