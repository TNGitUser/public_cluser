/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 00:51:40 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:03:40 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	phong(t_scene *s, t_vec3 il)
{
	double	dot;
	t_vec3	specular;

	specular = v3_scp(s->hit.nrm, (2. * v3_dot(il, s->hit.nrm)));
	specular = v3_nor(v3_dif(il, specular));
	dot = v3_dot(specular, s->hit.ray->dir);
	dot = dot < EPSILON ? 0 : dot;
	dot = pow(dot, s->hit.obj->shi[0]) * s->hit.obj->shi[1];
	return (dot);
}

static double	lambert(t_scene *s, t_vec3 il)
{
	double	dot;

	dot = v3_dot(il, s->hit.nrm);
	dot = dot < EPSILON ? 0 : dot;
	return (dot);
}

double			classic_shader(t_scene *s, t_vec3 il)
{
	return (lambert(s, il) + phong(s, il));
}

double			camera_shader(t_scene *s, t_vec3 il)
{
	double dot;

	dot = v3_dot(il, s->cam.w);
	dot = dot < 0 ? 0 : dot;
	return (dot);
}
