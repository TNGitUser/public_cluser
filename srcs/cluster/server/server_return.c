/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_return.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:15:52 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/30 14:56:52 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char	*get_line(char **data)
{
	int	i;
	int	cr;

	i = 0;
	cr = 0;
	if (!data || **data == '\0')
		return (NULL);
	while (*data && **data != '\n')
	{
		++i;
		++*data;
	}
	if (**data == '\n')
	{
		++(*data);
		++cr;
	}
	return (ft_strsub(*data - i - cr, 0, i)); 
}

static void	server_process_data(t_scene *s, t_node *node, char *data, int id)
{
	int		i[2];
	char	*line;
	int		index;

	//i[0] = node->clients[id].start[1];
	i[0] = 0;
	while (i[0] < s->mlx.wid)
	{
		i[1] = node->clients[id].start[1];
		while (i[1] < node->clients[id].end[1])
		{
			//index = 4 * (i[0] * s->mlx.wid) + 4 * i[1];
			index = ((s->mlx.hei - 1 - i[1]) * s->mlx.wid + i[0]) << 2;
			line = get_line(&data);
			*((int *)(s->mlx.loader_str + index)) = ft_atoi(line);
			ft_memdel((void *)&line);
			++(i[1]);
		}
		++(i[0]);
	}
}

void		server_assemble(void *sv)
{
	int		i;
	t_node	*node;
	t_scene *s;

	s = (t_scene *)sv;
	i = 0;
	node = &(s->info);
	while (i < MAXCON)
	{
		if (node->computed[i])
			server_process_data(s, node, node->computed_scene[i], i);
		++i;
	}
	printf("Done\n");
}

void	*server_get(void *ret)
{
	ssize_t	len;
	int		id;
	t_scene *s;
	t_node	*node;
	t_ret	*r;

	r = (t_ret *)ret;
	node = r->node;
	id = r->cl_id;
	s = (t_scene *)node->s_ptr;
	printf("Awaiting image data from %s\n", node->clients[id].name);
	receive_client_file(node, node->clients[id].socket, id, &len);
	if (len <= 0)
		error("Dead");
	else
	{
		node->computed[id] = 1;
		/*s->mlx.ptr = mlx_init();
		s->mlx.win = mlx_new_window(s->mlx.ptr, s->mlx.wid, s->mlx.hei
				, s->mlx.title);
		s->mlx.loader_ptr = mlx_new_image(s->mlx.ptr, s->mlx.wid, s->mlx.hei);
		s->mlx.loader_str = mlx_get_data_addr(s->mlx.loader_ptr, &s->mlx.b
				, &s->mlx.s
				, &s->mlx.e);
		server_assemble(s, s->mlx.loader_ptr);
		server_loop_mlx(s);*/
	}
	pthread_exit(NULL);
	return (NULL);
}
