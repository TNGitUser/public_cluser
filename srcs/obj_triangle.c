/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 04:58:33 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:09:09 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "triangles.h"

t_vec3			normal_triangle(t_hit *hit, t_ray *r)
{
	t_vec3 u;
	t_vec3 v;
	t_vec3 nrm;

	u = v3_dif(hit->obj->tr->v1, hit->obj->tr->v0);
	v = v3_dif(hit->obj->tr->v2, hit->obj->tr->v0);
	nrm = v3_nor(v3_cro(u, v));
	if (v3_dot(nrm, r->dir) < 0)
		return (nrm);
	return (v3_neg(nrm));
}

static void		motion_triangle_data(t_itrn *tr, t_ray *r, t_obj *o)
{
	t_vec3	move;

	move = v3_scd(o->blur, *r->maxtime);
	move = v3_scp(move, r->time);
	tr->v0 = v3_add(tr->v0, v3_neg(move));
	tr->v1 = v3_add(tr->v1, v3_neg(move));
	tr->v2 = v3_add(tr->v2, v3_neg(move));
}

static void		init_triangle_data(t_itrn *tr, t_ray *r, t_obj *o)
{
	tr->v0 = o->tr->v0;
	tr->v1 = o->tr->v1;
	tr->v2 = o->tr->v2;
	tr->e0 = v3_dif(tr->v1, tr->v0);
	tr->e1 = v3_dif(tr->v2, tr->v0);
	tr->h0 = v3_cro(r->dir, tr->e1);
	tr->a = v3_dot(tr->e0, tr->h0);
	if (r->time > 0)
		motion_triangle_data(tr, r, o);
}

void			intersect_ray_triangle(t_ray *r, t_obj *o, double *t)
{
	t_itrn	tr;
	double	te;

	init_triangle_data(&tr, r, o);
	if (tr.a > -EPSILON && tr.a < EPSILON)
		return ;
	tr.f = 1.0 / tr.a;
	tr.s0 = v3_dif(r->ori, tr.v0);
	tr.u = tr.f * v3_dot(tr.s0, tr.h0);
	if (tr.u < 0.0 || tr.u > 1.0)
		return ;
	tr.q0 = v3_cro(tr.s0, tr.e0);
	tr.v = tr.f * v3_dot(r->dir, tr.q0);
	if (tr.v < 0.0 || tr.u + tr.v > 1.0)
		return ;
	te = tr.f * v3_dot(tr.e1, tr.q0);
	if (te > EPSILON)
	{
		t[0] = te;
		t[1] = 0;
	}
}
