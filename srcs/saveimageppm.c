/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saveimageppm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:19:15 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:03:13 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		generate_file(char *name)
{
	static int	nb;
	char		*str[4];
	int			i;
	int			fd;

	str[0] = "./screenshots_ppm/";
	str[1] = ft_itoa(nb + 1);
	str[2] = ".ppm";
	i = 18 + ft_strlen(name) + ft_strlen(str[1]) + 4;
	str[3] = (char*)ft_secmemalloc(sizeof(char) * (i + 1));
	ft_strcpy(str[3], str[0]);
	ft_strcpy(&str[3][18], name);
	ft_strcpy(&str[3][18 + ft_strlen(name)], str[1]);
	ft_strcpy(&str[3][18 + ft_strlen(name) + ft_strlen(str[1])], str[2]);
	str[3][18 + ft_strlen(name) + ft_strlen(str[1]) + 4] = '\0';
	fd = open(str[3], O_WRONLY | O_TRUNC | O_CREAT, 0755);
	ft_strdel(&str[1]);
	ft_strdel(&str[3]);
	if (fd == -1)
		ft_putstr("error saving image\n");
	nb++;
	return (fd);
}

static void		put_header(int wid, int hei, int fd)
{
	char *temp;

	ft_putstr_fd("P3\n", fd);
	temp = ft_itoa(wid);
	ft_putstr_fd(temp, fd);
	ft_strdel(&temp);
	ft_putchar_fd(' ', fd);
	temp = ft_itoa(hei);
	ft_putstr_fd(temp, fd);
	ft_strdel(&temp);
	ft_putchar_fd('\n', fd);
	ft_putstr_fd("255\n", fd);
}

static void		chantoascii(unsigned int channel, char *str)
{
	int				len;
	unsigned int	temp;

	temp = channel;
	len = 0;
	if (temp == 0)
		len = 1;
	while (temp)
	{
		temp *= 0.1;
		len++;
	}
	str[len] = '\0';
	while (len)
	{
		str[len - 1] = (channel % 10) + 48;
		channel *= 0.1;
		len--;
	}
}

static void		put_pixgrid(int wid, int hei, int fd, unsigned char *str_value)
{
	char			temp[4];
	long int		max_pos;
	long int		max_line;
	long int		i;

	max_line = wid * 4;
	max_pos = max_line * hei;
	i = 0;
	while (i < max_pos)
	{
		chantoascii(str_value[i + 2], temp);
		ft_putstr_fd(temp, fd);
		ft_putchar_fd(' ', fd);
		chantoascii(str_value[i + 1], temp);
		ft_putstr_fd(temp, fd);
		ft_putchar_fd(' ', fd);
		chantoascii(str_value[i + 0], temp);
		ft_putstr_fd(temp, fd);
		ft_putchar_fd(' ', fd);
		i += 4;
		if (i > 0 && i % max_line == 0)
			ft_putchar_fd('\n', fd);
	}
}

void			saving_image_ppm(t_scene *s)
{
	int			fd;

	fd = generate_file(s->mlx.title);
	put_header(s->mlx.wid, s->mlx.hei, fd);
	put_pixgrid(s->mlx.wid, s->mlx.hei, fd, (unsigned char*)s->mlx.pst);
}
