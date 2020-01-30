/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_single.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:22:19 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/20 10:26:12 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	normal_at(t_hit *hit, t_normal f)
{
	double	world_isc[4][1];
	double	objec_isc[4][1];
	double	objec_nrm[4][1];
	double	world_nrm[4][1];
	t_vec3	vectr_nrm;

	ft_ptom(hit->isc, world_isc);
	m44d41(hit->obj->mtx, world_isc, objec_isc);
	(f)(objec_isc, objec_nrm);
	m44d41(hit->obj->trx, objec_nrm, world_nrm);
	vectr_nrm.x = world_nrm[0][0];
	vectr_nrm.y = world_nrm[1][0];
	vectr_nrm.z = world_nrm[2][0];
	vectr_nrm = v3_scp(vectr_nrm, hit->obj->inv_nrm);
	return (v3_nor(vectr_nrm));
}

t_vec3	get_norm(t_hit *hit, t_ray *r)
{
	if (hit->obj->typ == 0 || hit->obj->typ == 4)
		return (hit->obj->dir);
	else if (hit->obj->typ == 1)
		return (normal_at(hit, &normal_sphere));
	else if (hit->obj->typ == 2)
		return (normal_at(hit, &normal_cylinder));
	else if (hit->obj->typ == 3)
		return (normal_at(hit, &normal_cone));
	else if (hit->obj->typ == 5)
		return (normal_triangle(hit, r));
	return (v3(0, 0, 0));
}

t_vec3	orientate_axes(t_scene *s, double x, double y)
{
	t_vec3	ret;

	ret = v3_add(s->cam.bottleft, v3_scp(s->cam.vi_x, x));
	ret = v3_add(ret, v3_scp(s->cam.vi_y, y));
	ret = v3_nor(ret);
	return (ret);
}

int		single_ray(t_scene *s, t_ray *r, double x, double y)
{
	r->dir = orientate_axes(s, x, y);
	s->hit.ray = r;
	r->maxtime = &s->efc.maxtime;
	collect_object_isc(s, r);
	get_object_hit(s);
	free_void_region(s);
	if (s->hit.t != INFINITY)
	{
		if (s->hit.obj->id >= ID_OFFSET)
			return (0xffffff);
		s->hit.nrm = get_norm(&s->hit, r);
		return (light(s, &classic_shader));
	}
	if (s->cam.glr.select < 1)
		return (0);
	return (camera_light(s, 0));
}
