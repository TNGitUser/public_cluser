/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:39:58 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:12:41 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3		find_intersection_point(t_ray *r, double *t)
{
	t_vec3 intsc;

	intsc = v3_scp(r->dir, *t);
	intsc = v3_add(intsc, r->ori);
	return (intsc);
}

void		shadow_intersection(t_obj *o, t_ray *r, double *t)
{
	if (o->typ == 0)
		intersect_ray_plane(r, o, t);
	else if (o->typ == 1)
		intersect_ray_sphere(r, o, t);
	else if (o->typ == 2)
		intersect_ray_cylinder(r, o, t);
	else if (o->typ == 3)
		intersect_ray_cone(r, o, t);
	else if (o->typ == 4)
		intersect_ray_disk(r, o, t);
	else if (o->typ == 5)
		if (o->id < ID_OFFSET)
			intersect_ray_triangle(r, o, t);
}

void		object_intersection(t_obj *o, t_ray *r, double *t)
{
	if (o->typ == 0)
		intersect_ray_plane(r, o, t);
	else if (o->typ == 1)
		intersect_ray_sphere(r, o, t);
	else if (o->typ == 2)
		intersect_ray_cylinder(r, o, t);
	else if (o->typ == 3)
		intersect_ray_cone(r, o, t);
	else if (o->typ == 4)
		intersect_ray_disk(r, o, t);
	else if (o->typ == 5)
		intersect_ray_triangle(r, o, t);
	o->inv_nrm = 1;
	if (t[0] && t[1] && ((t[0] < 0 && t[1] > 0) || (t[0] > 0 && t[1] < 0)))
		o->inv_nrm = -1;
}
