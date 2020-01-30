/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:07:49 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/02 22:07:52 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		finish(void)
{
	ft_putstr("Program closed correctly\n");
	exit(EXIT_SUCCESS);
}

int		mouse_loop(int k, int x, int y, t_scene *s)
{
	x = y;
	if (k == 5)
		s->cam.fov += (s->cam.fov < 170 ? 10 : 0);
	else if (k == 4)
		s->cam.fov -= (s->cam.fov > 10 ? 10 : 0);
	if (k == 4 || k == 5)
	{
		ft_bzero(s->mlx.pst, s->mlx.wid * s->mlx.hei * 4);
		select_image_mode(s);
	}
	return (0);
}
