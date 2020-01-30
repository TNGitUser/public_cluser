/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 02:34:50 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/20 12:07:25 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	spot_light(t_scene *s, t_lht *l, t_shader f)
{
	t_ray	lightray;
	double	lightdist;
	double	spherdist;
	double	cone[2];

	lightray.ori = s->hit.isc;
	lightray.dir = v3_dif(l->s->pos, lightray.ori);
	lightdist = v3_le2(v3(0, 0, 0), lightray.dir);
	lightray.dir = v3_nor(lightray.dir);
	lightray.time = s->hit.ray->time;
	lightray.maxtime = &s->efc.maxtime;
	collect_shadow_isc(s, &lightray);
	get_shadow_hit(s);
	if ((s->hit.t * s->hit.t) < lightdist)
		return (0);
	spherdist = lightdist * 4 * M_PI;
	cone[0] = v3_dot(v3_nor(l->s->dir), v3_neg(lightray.dir));
	cone[1] = cos(l->s->ang / 2.);
	if (cone[0] >= cone[1])
		return (f(s, lightray.dir) * l->pow / spherdist);
	return (0);
}

double	direction_light(t_scene *s, t_lht *l, t_shader f)
{
	t_ray	lightray;

	lightray.ori = s->hit.isc;
	lightray.dir = v3_nor(v3_neg(l->d->dir));
	lightray.time = s->hit.ray->time;
	lightray.maxtime = &s->efc.maxtime;
	collect_shadow_isc(s, &lightray);
	get_shadow_hit(s);
	if (s->hit.t < INFINITY)
		return (0);
	return (f(s, lightray.dir) * l->pow * 0.000001);
}

double	point_light(t_scene *s, t_lht *l, t_shader f)
{
	t_ray	lightray;
	double	lightdist;
	double	spherdist;

	lightray.ori = s->hit.isc;
	lightray.dir = v3_dif(l->p->pos, lightray.ori);
	lightdist = v3_le2(v3(0, 0, 0), lightray.dir);
	lightray.dir = v3_nor(lightray.dir);
	lightray.time = s->hit.ray->time;
	lightray.maxtime = &s->efc.maxtime;
	collect_shadow_isc(s, &lightray);
	get_shadow_hit(s);
	if ((s->hit.t * s->hit.t) < lightdist)
		return (0);
	spherdist = lightdist * 4 * M_PI;
	return (f(s, lightray.dir) * l->pow / spherdist);
}

int		light(t_scene *s, t_shader f)
{
	double	en[s->n_lht];
	int		i;

	i = -1;
	while (++i < s->n_lht)
	{
		en[i] = 0;
		if (s->lht[i].typ == 1)
			en[i] += point_light(s, &s->lht[i], f);
		else if (s->lht[i].typ == 2)
			en[i] += direction_light(s, &s->lht[i], f);
		else if (s->lht[i].typ == 3)
			en[i] += spot_light(s, &s->lht[i], f);
		else if (s->lht[i].typ == 4)
			en[i] += rectangle_light(s, &s->lht[i], f);
		free_void_region(s);
	}
	if (s->cam.glr.select < 1)
		return (get_color(s, en, s->hit.obj->clr, s->pix.amb));
	return (camera_light(s, get_color(s, en, s->hit.obj->clr, s->pix.amb)));
}
