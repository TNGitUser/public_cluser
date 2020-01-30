/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_trn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 20:45:52 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:02:29 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		rotate_triangle(t_obj *o, t_vec3 *center)
{
	double	m_rtx[4][4];
	double	m_ve0[4][1];
	double	m_ve1[4][1];
	double	m_ve2[4][1];

	if (o->typ != 5)
		return ;
	obj_rotations(o, m_rtx);
	o->tr->v0 = v3_dif(o->tr->v0, *center);
	o->tr->v1 = v3_dif(o->tr->v1, *center);
	o->tr->v2 = v3_dif(o->tr->v2, *center);
	m41_prp(&o->tr->v0, m_rtx, m_ve0);
	m41_prp(&o->tr->v1, m_rtx, m_ve1);
	m41_prp(&o->tr->v2, m_rtx, m_ve2);
	o->tr->v0 = mtov(m_ve0);
	o->tr->v1 = mtov(m_ve1);
	o->tr->v2 = mtov(m_ve2);
	o->tr->v0 = v3_add(o->tr->v0, *center);
	o->tr->v1 = v3_add(o->tr->v1, *center);
	o->tr->v2 = v3_add(o->tr->v2, *center);
}

static void	rotate_mesh_aux(t_scene *s, int *i, t_vec3 center)
{
	obj_translation(&s->obj[*i]);
	center = v3_add(s->obj[*i].tr->v0, center);
	center = v3_add(s->obj[*i].tr->v1, center);
	center = v3_add(s->obj[*i].tr->v2, center);
}

void		rotate_mesh(t_scene *s, int *i)
{
	t_vec3	center;
	int		id;
	int		start;
	double	total_v;

	center = v3(0, 0, 0);
	total_v = 0;
	id = s->obj[*i].id;
	start = *i - 1;
	while (*i < s->n_obj && &s->obj[*i] && s->obj[*i].id == id)
	{
		if (s->obj[*i].typ != 5)
		{
			(*i)++;
			continue;
		}
		rotate_mesh_aux(s, i, center);
		(*i)++;
		total_v += 3;
	}
	center = v3_scd(center, total_v);
	while (++start < *i)
		rotate_triangle(&s->obj[start], &center);
	(*i)--;
}
