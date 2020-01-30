/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:02:44 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:11:15 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vec3	find_early_position(t_scene *s, t_lht *l)
{
	t_vec3	pos;
	t_int2	k;

	pos = v3(0, 0, 0);
	if (l->typ == 1)
		pos = l->p->pos;
	else if (l->typ == 2)
		pos = v3_add(s->cam.pos, v3_scp(s->cam.w, 2.));
	else if (l->typ == 3)
		pos = l->s->pos;
	else if (l->typ == 4)
	{
		k.i = l->a->q_v / 2.;
		k.j = l->a->q_u / 2.;
		pos = center_of_sample(k, l);
	}
	return (pos);
}

static void		fill_fake_planes(t_scene *s, int i)
{
	t_vec3	pos;

	s->cam.glr.fakeplane[i].typ = 0;
	s->cam.glr.fakeplane[i].id = 0;
	s->cam.glr.fakeplane[i].clr = 0;
	s->cam.glr.fakeplane[i].rot = v3(0, 0, 0);
	s->cam.glr.fakeplane[i].tra = v3(0, 0, 0);
	s->cam.glr.fakeplane[i].tr = NULL;
	s->cam.glr.fakeplane[i].pr->dim = 1;
	s->cam.glr.fakeplane[i].dir = v3_neg(s->cam.w);
	pos = find_early_position(s, &s->lht[i]);
	s->cam.glr.fakeplane[i].pr->pos = v3_add(pos, s->cam.glr.fakeplane[i].dir);
	add_transform_to_obj(&s->cam.glr.fakeplane[i]);
}

static void		precalc_planes(t_scene *s, t_shader f)
{
	int i;

	if (s->cam.glr.select == 2)
	{
		s->hit.isc = s->cam.pos;
		i = -1;
		while (++i < s->n_lht)
		{
			if (s->lht[i].typ == 1 && point_light(s, &s->lht[i], f) > 0)
				s->cam.glr.shadow[i] = 1;
			if (s->lht[i].typ == 2 && direction_light(s, &s->lht[i], f) > 0)
				s->cam.glr.shadow[i] = 1;
			if (s->lht[i].typ == 3 && spot_light(s, &s->lht[i], f) > 0)
				s->cam.glr.shadow[i] = 1;
			if (s->lht[i].typ == 4 && rectangle_light(s, &s->lht[i], f) > 0)
				s->cam.glr.shadow[i] = 1;
			fill_fake_planes(s, i);
		}
		s->cam.glr.select = 3;
	}
}

static double	cam_light_amount(t_scene *s, t_lht *l, t_obj *o)
{
	t_vec3	jolly_vec;
	t_vec3	fake_isc;
	double	t[2];
	double	fake_dist;
	double	light_dist;

	if (l->typ == 2)
		return (l->pow * 0.00001);
	intersect_ray_plane(s->hit.ray, o, t);
	fake_isc = find_intersection_point(s->hit.ray, t);
	jolly_vec = v3_dif(o->pr->pos, fake_isc);
	fake_dist = sqrt(sqrt(v3_dot(jolly_vec, jolly_vec))) * M_PI * 4 + ANULL;
	jolly_vec = v3_dif(o->pr->pos, s->cam.pos);
	light_dist = v3_dot(jolly_vec, jolly_vec) + ANULL;
	if (l->typ == 4)
		return (l->pow * 2. / fake_dist / light_dist * 4.);
	return (l->pow / fake_dist / light_dist * 4.);
}

double			camera_light(t_scene *s, int color)
{
	double		en[s->n_lht];
	int			i;

	precalc_planes(s, &camera_shader);
	i = -1;
	while (++i < s->n_lht)
	{
		en[i] = 0;
		if (s->cam.glr.shadow[i] > 0)
			en[i] += cam_light_amount(s, &s->lht[i], &s->cam.glr.fakeplane[i]);
	}
	return (get_color(s, en, color, 1));
}
