/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:17:54 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/16 17:35:59 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			normal_cylinder(double pnt[4][1], double dst[4][1])
{
	dst[0][0] = pnt[0][0];
	dst[1][0] = 0;
	dst[2][0] = pnt[2][0];
}

static void		equation(t_vec3 *coef, double *disc, double *t)
{
	t[0] = (sqrt(*disc) - coef->y) / (2.0 * coef->x);
	t[1] = (-sqrt(*disc) - coef->y) / (2.0 * coef->x);
	t[2] = 0;
}

void			intersect_ray_cylinder(t_ray *r, t_obj *o, double *t)
{
	double	disc;
	t_vec3	coef;
	t_ray	tr;

	tr = transform_ray(r, o);
	coef.x = (tr.dir.x * tr.dir.x) + (tr.dir.z * tr.dir.z);
	if (coef.x == 0)
		return ;
	coef.y = 2. * tr.ori.x * tr.dir.x + 2. * tr.ori.z * tr.dir.z;
	coef.z = (tr.ori.x * tr.ori.x) + (tr.ori.z * tr.ori.z) - 1.;
	disc = coef.y * coef.y - 4. * coef.x * coef.z;
	if (disc < 0)
		return ;
	equation(&coef, &disc, t);
}
