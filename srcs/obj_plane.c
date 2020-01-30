/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:57:22 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/15 22:11:47 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		intersect_ray_plane(t_ray *r, t_obj *o, double *t)
{
	t_ray	tr;

	tr = transform_ray(r, o);
	if (fabs(tr.dir.y) < EPSILON)
	{
		t[0] = 0;
		return ;
	}
	t[0] = -tr.ori.y / tr.dir.y;
	t[1] = 0;
}
