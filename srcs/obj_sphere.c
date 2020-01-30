/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:57:32 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/30 20:18:19 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		normal_sphere(double pnt[4][1], double dst[4][1])
{
	dst[0][0] = pnt[0][0];
	dst[1][0] = pnt[1][0];
	dst[2][0] = pnt[2][0];
}

static void	equation(t_vec3 *coef, double *disc, double *t)
{
	t[0] = (sqrt(*disc) - coef->y) / (2.0 * coef->x);
	t[1] = (-sqrt(*disc) - coef->y) / (2.0 * coef->x);
	t[2] = 0;
}

void		intersect_ray_sphere(t_ray *r, t_obj *o, double *t)
{
	double	disc;
	t_vec3	coef;
	t_vec3	dist;
	t_ray	tr;

	tr = transform_ray(r, o);
	dist = tr.ori;
	coef.x = v3_dot(tr.dir, tr.dir);
	coef.y = 2 * v3_dot(tr.dir, dist);
	coef.z = v3_dot(dist, dist) - 1;
	disc = coef.y * coef.y - 4 * coef.x * coef.z;
	if (disc < 0)
		return ;
	equation(&coef, &disc, t);
}
