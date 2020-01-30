/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:56:34 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:09:32 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			normal_cone(double pnt[4][1], double dst[4][1])
{
	dst[0][0] = pnt[0][0];
	dst[2][0] = pnt[2][0];
	dst[1][0] = sqrt(pnt[0][0] * pnt[0][0] + pnt[2][0] * pnt[2][0]);
	if (pnt[1][0] > 0)
		dst[1][0] *= -1;
}

static void		equation(t_vec3 *coef, double *disc, double *t)
{
	if (coef->x < EPSILON && coef->x > -EPSILON)
	{
		if (coef->y < EPSILON && coef->y > -EPSILON)
			return ;
		t[0] = -coef->z / 2. * coef->y;
		t[1] = 0;
		return ;
	}
	t[0] = (sqrt(*disc) - coef->y) / (2. * coef->x);
	t[1] = (-sqrt(*disc) - coef->y) / (2. * coef->x);
	t[2] = 0;
}

void			intersect_ray_cone(t_ray *r, t_obj *o, double *t)
{
	double	disc;
	t_vec3	coef;
	t_ray	tr;

	tr = transform_ray(r, o);
	coef.x = (tr.dir.x * tr.dir.x) - (tr.dir.y * tr.dir.y)
		+ (tr.dir.z * tr.dir.z);
	coef.y = 2. * tr.ori.x * tr.dir.x - 2. * tr.ori.y * tr.dir.y
		+ 2. * tr.ori.z * tr.dir.z;
	coef.z = (tr.ori.x * tr.ori.x) - (tr.ori.y * tr.ori.y)
		+ (tr.ori.z * tr.ori.z);
	disc = coef.y * coef.y - 4. * coef.x * coef.z;
	if (disc < 0)
		return ;
	equation(&coef, &disc, t);
}
