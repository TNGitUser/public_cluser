/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_timed_cam.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:47:21 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:07:49 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	motion_blur_x(t_scene *s, t_ray *r, t_crd2 c, t_render f)
{
	int			color[abs(s->efc.blu[1]) + 1]; // WARNING : Not allowed
	double		temp;
	int			i;

	i = -1;
	temp = r->ori.x;
	while (++i < abs(s->efc.blu[1]))
	{
		color[i] = (f)(s, r, c.x, c.y);
		if (s->efc.blu[1] > 0)
			r->ori.x++;
		else
			r->ori.x--;
	}
	r->ori.x = temp;
	return (average_color(color, abs(s->efc.blu[1] + 1)));
}

static int	motion_blur_y(t_scene *s, t_ray *r, t_crd2 c, t_render f)
{
	int			color[abs(s->efc.blu[1]) + 1]; // WARNING : Not allowed
	double		temp;
	int			i;

	i = -1;
	temp = r->ori.y;
	while (++i < abs(s->efc.blu[1]))
	{
		color[i] = (f)(s, r, c.x, c.y);
		if (s->efc.blu[1] > 0)
			r->ori.y++;
		else
			r->ori.y--;
	}
	r->ori.y = temp;
	return (average_color(color, abs(s->efc.blu[1] + 1)));
}

int			global_blur(t_scene *s, t_ray *r, double x, double y)
{
	t_crd2	c;

	c.x = x;
	c.y = y;
	if (s->efc.blu[0] == 1)
	{
		if (s->efc.toon != 0)
			return (motion_blur_x(s, r, c, &cartoon_effect));
		else if (s->efc.aa != 0)
			return (motion_blur_x(s, r, c, &antialiasing));
		else
			return (motion_blur_x(s, r, c, &single_ray));
	}
	else if (s->efc.blu[0] == 2)
	{
		if (s->efc.toon != 0)
			return (motion_blur_y(s, r, c, &cartoon_effect));
		else if (s->efc.aa != 0)
			return (motion_blur_y(s, r, c, &antialiasing));
		else
			return (motion_blur_y(s, r, c, &single_ray));
	}
	return (0);
}
