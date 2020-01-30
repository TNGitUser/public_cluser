/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders_cartoon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 01:19:34 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 14:59:35 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	toon_lambert(t_scene *s, t_vec3 il)
{
	double	dot;

	dot = v3_dot(il, s->hit.nrm);
	if (dot < 0.2)
		dot = 0;
	if (dot >= 0.2 && dot < 0.4)
		dot = 0.2;
	if (dot >= 0.2 && dot < 0.5)
		dot = 0.5;
	if (dot >= 0.5)
		dot = 1;
	return (dot);
}

static double	toon_phong(t_scene *s, t_vec3 il)
{
	double	dot;
	t_vec3	specular;

	il = v3_neg(il);
	specular = v3_scp(s->hit.nrm, (2 * v3_dot(il, s->hit.nrm)));
	specular = v3_nor(v3_dif(specular, il));
	dot = v3_dot(specular, s->hit.ray->dir);
	dot = (dot < 0.95) ? 0 : 1;
	dot = pow(dot, s->hit.obj->shi[0]) * s->hit.obj->shi[1];
	return (dot);
}

double			cartoon_shader(t_scene *s, t_vec3 il)
{
	return (toon_lambert(s, il) + toon_phong(s, il));
}
