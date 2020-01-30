/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_disk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 20:40:17 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/15 22:11:54 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	check_plane_intersection(t_ray *r, double *t)
{
	if (fabs(r->dir.y) < EPSILON)
		return ;
	t[0] = -r->ori.y / r->dir.y;
	t[1] = 0;
}

void	intersect_ray_disk(t_ray *r, t_obj *o, double *t)
{
	double	dist;
	t_ray	tr;
	t_vec3	intsc;

	tr = transform_ray(r, o);
	check_plane_intersection(&tr, t);
	if (t[0] != 0)
	{
		intsc = find_intersection_point(&tr, t);
		dist = v3_dot(intsc, intsc);
		if (dist > 1)
			t[0] = 0;
	}
}
