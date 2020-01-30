/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_timed_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:47:48 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:05:22 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double		determinate_max_time(t_scene *s)
{
	int		i;
	double	current;

	s->efc.maxtime = 0;
	current = 0;
	i = -1;
	while (++i < s->n_obj)
	{
		if (v3_cmp(v3(0, 0, 0), s->obj[i].blur) == 0)
		{
			current = v3_len(s->obj[i].blur, v3(0, 0, 0));
			if ((fabs(current)) > s->efc.maxtime)
				s->efc.maxtime = fabs(current);
		}
	}
	if ((s->efc.maxtime) && (s->efc.maxtime > 20 || s->efc.maxtime < 2))
		error("The lenght of the motion vector is out of range");
	return (0);
}

int			time_travel(t_scene *s, t_ray *r, t_crd2 c, t_render f)
{
	int	color[(int)s->efc.maxtime + 1]; // WARNING : This is not allowed

	r->time = -1;
	while (++r->time < s->efc.maxtime)
		color[(int)(r->time)] = (f)(s, r, c.x, c.y);
	return (average_color(color, s->efc.maxtime));
}

int			timed_rays(t_scene *s, t_ray *r, double x, double y)
{
	t_crd2	c;

	c.x = x;
	c.y = y;
	if (s->efc.maxtime != 0)
	{
		if (s->efc.toon != 0)
			return (time_travel(s, r, c, &cartoon_effect));
		else if (s->efc.aa != 0)
			return (time_travel(s, r, c, &antialiasing));
		else
			return (time_travel(s, r, c, &single_ray));
	}
	error("Something gone wrong with object motion");
	return (0);
}
