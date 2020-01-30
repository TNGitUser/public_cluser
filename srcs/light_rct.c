/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_rct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 01:15:22 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/03 00:57:57 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3			center_of_sample(t_int2 k, t_lht *l)
{
	t_vec3	center;
	t_crd2	c;
	t_vec3	u;
	t_vec3	v;

	c.x = (double)k.i;
	c.y = (double)k.j;
	v = v3_scp(l->a->u_v, (c.x + 0.5));
	u = v3_scp(l->a->u_u, (c.y + 0.5));
	center = v3_add(l->a->pos, u);
	center = v3_add(center, v);
	return (center);
}

static void		fill_sample_data(t_lht *sample, t_lht *l)
{
	sample->s = (t_slt*)ft_secmemalloc(sizeof(t_slt));
	sample->pow = l->pow / (l->a->q_v * l->a->q_u);
	sample->clr = l->clr;
	sample->typ = 3;
	sample->s->dir = v3_cro(v3_nor(l->a->v), v3_nor(l->a->u));
	sample->s->dir = v3_scp(sample->s->dir, l->a->inv);
	sample->s->ang = 3.14159265358979;
}

double			rectangle_light(t_scene *s, t_lht *l, t_shader f)
{
	t_lht	sample;
	double	en;
	t_int2	k;

	l->a->u_v = v3_scd(l->a->v, l->a->q_v);
	l->a->u_u = v3_scd(l->a->u, l->a->q_u);
	fill_sample_data(&sample, l);
	en = 0;
	k.j = -1;
	while (++k.j < l->a->q_u)
	{
		k.i = -1;
		while (++k.i < l->a->q_v)
		{
			sample.s->pos = center_of_sample(k, l);
			en += spot_light(s, &sample, f);
		}
	}
	ft_memdel((void*)&sample.s);
	return (en);
}
