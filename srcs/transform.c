/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 20:36:59 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/30 23:30:48 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		obj_translation(t_obj *o)
{
	if (o->pr)
		o->pr->pos = v3_add(o->pr->pos, o->tra);
	else if (o->tr)
	{
		o->tr->v0 = v3_add(o->tr->v0, o->tra);
		o->tr->v1 = v3_add(o->tr->v1, o->tra);
		o->tr->v2 = v3_add(o->tr->v2, o->tra);
	}
}

void		obj_rotations(t_obj *o, double rot[4][4])
{
	double	m_x[4][4];
	double	m_y[4][4];
	double	m_z[4][4];
	double	m_t[4][4];

	m44_rtx(o->rot.x, m_x);
	m44_rty(o->rot.y, m_y);
	m44_rtz(o->rot.z, m_z);
	m44_dot(m_x, m_y, m_t);
	m44_dot(m_t, m_z, rot);
}

void		add_transform_to_obj(t_obj *o)
{
	double	m_sca[4][4];
	double	m_dir[4][4];
	double	m_rtx[4][4];
	double	m_mov[4][4];
	double	m_tmp[4][4];

	if (o->typ == 3)
		m44_sca(o->pr->dim, -1., o->pr->dim, m_tmp);
	else
		m44_sca(o->pr->dim, o->pr->dim, o->pr->dim, m_tmp);
	m44_inv(m_tmp, m_sca);
	m44_rtv(o->dir, v3(0, 1, 0), m_tmp);
	m44_inv(m_tmp, m_dir);
	obj_rotations(o, m_tmp);
	m44_dot(m_dir, m_tmp, m_rtx);
	m44_mov(-o->pr->pos.x, -o->pr->pos.y, -o->pr->pos.z, m_mov);
	m44_dot(m_sca, m_rtx, m_tmp);
	m44_dot(m_tmp, m_mov, o->mtx);
	m44_tra(o->mtx, o->trx);
}

t_ray		motion_ray(t_ray *r, t_obj *o, t_ray *tr)
{
	double	m[4][1];
	double	n_mtx[4][4];
	double	mov[4][4];
	t_vec3	move;

	move = v3_scd(o->blur, *r->maxtime);
	move = v3_scp(move, r->time);
	m44_mov(-move.x, -move.y, -move.z, mov);
	m44_dot(o->mtx, mov, n_mtx);
	m41_prp(&r->ori, n_mtx, m);
	tr->ori.x = m[0][0];
	tr->ori.y = m[1][0];
	tr->ori.z = m[2][0];
	m41_prv(&r->dir, n_mtx, m);
	tr->dir.x = m[0][0];
	tr->dir.y = m[1][0];
	tr->dir.z = m[2][0];
	return (*tr);
}

t_ray		transform_ray(t_ray *r, t_obj *o)
{
	t_ray	tr;
	double	m[4][1];

	if (r->time > 0)
		return (motion_ray(r, o, &tr));
	m41_prp(&r->ori, o->mtx, m);
	tr.ori.x = m[0][0];
	tr.ori.y = m[1][0];
	tr.ori.z = m[2][0];
	m41_prv(&r->dir, o->mtx, m);
	tr.dir.x = m[0][0];
	tr.dir.y = m[1][0];
	tr.dir.z = m[2][0];
	return (tr);
}
