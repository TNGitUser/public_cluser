/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_distributed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:50:56 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/02 22:50:58 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		average_color(int *rgb, int n)
{
	int		i;
	t_rgb	s;

	s.r = 0;
	s.g = 0;
	s.b = 0;
	i = -1;
	while (++i < n)
	{
		s.r += (rgb[i] >> 16) & 0xff;
		s.g += (rgb[i] >> 8) & 0xff;
		s.b += rgb[i] & 0xff;
	}
	s.r /= n;
	s.g /= n;
	s.b /= n;
	return (((s.r & 0x0ff) << 16) | ((s.g & 0x0ff) << 8) | (s.b & 0x0ff));
}

int		distribuited_rays(t_scene *s, t_ray *r, double x, double y)
{
	if (s->efc.select == 2)
		return (timed_rays(s, r, x, y));
	else if (s->efc.blu[0] != 0)
		return (global_blur(s, r, x, y));
	else if (s->efc.toon != 0)
		return (cartoon_effect(s, r, x, y));
	else if (s->efc.aa != 0)
		return (antialiasing(s, r, x, y));
	else
		return (0);
}
