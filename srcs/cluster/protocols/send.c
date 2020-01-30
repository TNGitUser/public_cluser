/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:33:45 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/30 14:55:29 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	write_ctf(char *img_ptr, int index, int fd, t_scene *s)
{
	char	*n;
	int		pix;

	(void)img_ptr;
	pix = *((int *)(s->mlx.pst + index));
	n = ft_itoa(pix);
	write(fd, n, ft_strlen(n));
	write(fd, "\n", 1);
	ft_memdel((void *)&n);
}

static void	image_to_string(ssize_t len, t_scene *s, int index, char *file)
{
	int		fd;
	ssize_t	i;
	ssize_t	j;
	char	*img_ptr;

	img_ptr = s->mlx.pst;
	if (len == 0)
		return ;
	if (!(fd = open(file, O_CREAT | O_RDWR, 0666)))
		error("Cannot open file to share computed pixels");
	i = 0;
	while (i < s->mlx.wid)
	{
		j = s->min_y;
		while (j < s->max_y)
		{
			//index = 4 * (j * s->mlx.wid) + 4 * i;
			index = ((s->mlx.hei - j - 1) * s->mlx.wid + i) << 2;
			write_ctf(img_ptr, index, fd, s);
			++j;
		}
		++i;
	}
	close(fd);
}

void	send_image(int client_fd, t_node *node)
{
	t_scene	*s;
	char	*data;
	ssize_t	img_len;
	char	*file;

	file = strjoin("computed.pixels.", node->info.name);
	//remove("computed.pixels");
	s = (t_scene *)(node->s_ptr);
	img_len = s->mlx.s * s->mlx.hei;
	image_to_string(img_len, s, 0, file);
	data = get_data_filename(file);
	send_file(data, node, client_fd);
	printf("Data sent\n");
	sleep(1);
	remove(file);
}

void	send_string(int client_fd, t_node *node, char *string)
{
	char			buffer[BUFFER_SIZE + 1];
	size_t			len;
	size_t			var;

	(void)node;
	len = strlen(string);
	var = htonl(len);
	send(client_fd, &var, sizeof(var), 0);
	strcpy(buffer, string);
	buffer[len] = '\0';
	send(client_fd, &buffer, len, 0);
	sleep(1);
}

/*
 **	CMD Example :	"SET		BOUNDS	0		0		250		250"
 **					 COMMAND	VAR		startX	startY	endX	endY
 */

void	send_command(t_node *node, char *cmd, int client_id)
{
	send_string(node->clients[client_id].socket, node, cmd);
}
