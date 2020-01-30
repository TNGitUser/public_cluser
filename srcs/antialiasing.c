/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:01:50 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/03 00:53:38 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		aa_x2(t_scene *s, t_ray *r, t_crd2 c, t_render f)
{
	int		color[2];

	color[0] = (f)(s, r, c.x + 0.10, c.y + 0.10);
	color[1] = (f)(s, r, c.x - 0.35, c.y - 0.35);
	return (average_color(color, 2));
}

int		aa_x4(t_scene *s, t_ray *r, t_crd2 c, t_render f)
{
	int		color[4];

	color[0] = (f)(s, r, c.x - 0.25, c.y + 0.25);
	color[1] = (f)(s, r, c.x + 0.25, c.y + 0.25);
	color[2] = (f)(s, r, c.x - 0.25, c.y - 0.25);
	color[3] = (f)(s, r, c.x + 0.25, c.y - 0.25);
	return (average_color(color, 4));
}

int		antialiasing(t_scene *s, t_ray *r, double x, double y)
{
	t_crd2	c;

	c.x = x;
	c.y = y;
	if (s->efc.aa == 2)
		return (aa_x2(s, r, c, &single_ray));
	else if (s->efc.aa == 4)
		return (aa_x4(s, r, c, &single_ray));
	else
		return (0);
}
