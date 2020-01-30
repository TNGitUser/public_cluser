/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_qtn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 20:49:05 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/23 20:49:08 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	quaternion_rotation_x(t_scene *s, t_vec3 axe)
{
	t_vec4	rot;
	t_vec4	qaxe;
	t_vec4	res;
	t_vec3	naxe;

	rot.x = s->cam.v.x * sin(s->cam.rot.x / 2.);
	rot.y = s->cam.v.y * sin(s->cam.rot.x / 2.);
	rot.z = s->cam.v.z * sin(s->cam.rot.x / 2.);
	rot.w = cos(s->cam.rot.x / 2.);
	qaxe.x = axe.x;
	qaxe.y = axe.y;
	qaxe.z = axe.z;
	qaxe.w = 0.;
	res = v4_dot(v4_dot(rot, qaxe), v4_con(rot));
	naxe = v3(res.x, res.y, res.z);
	return (naxe);
}

t_vec3	quaternion_rotation_y(t_scene *s, t_vec3 axe)
{
	t_vec4	rot;
	t_vec4	qaxe;
	t_vec4	res;
	t_vec3	naxe;

	rot.x = s->cam.u.x * sin(s->cam.rot.y / 2.);
	rot.y = s->cam.u.y * sin(s->cam.rot.y / 2.);
	rot.z = s->cam.u.z * sin(s->cam.rot.y / 2.);
	rot.w = cos(s->cam.rot.y / 2.);
	qaxe.x = axe.x;
	qaxe.y = axe.y;
	qaxe.z = axe.z;
	qaxe.w = 0.;
	res = v4_dot(v4_dot(rot, qaxe), v4_con(rot));
	naxe = v3(res.x, res.y, res.z);
	return (naxe);
}

t_vec3	quaternion_rotation_z(t_scene *s, t_vec3 axe)
{
	t_vec4	rot;
	t_vec4	qaxe;
	t_vec4	res;
	t_vec3	naxe;

	rot.x = s->cam.w.x * sin(s->cam.rot.z / 2.);
	rot.y = s->cam.w.y * sin(s->cam.rot.z / 2.);
	rot.z = s->cam.w.z * sin(s->cam.rot.z / 2.);
	rot.w = cos(s->cam.rot.z / 2.);
	qaxe.x = axe.x;
	qaxe.y = axe.y;
	qaxe.z = axe.z;
	qaxe.w = 0.;
	res = v4_dot(v4_dot(rot, qaxe), v4_con(rot));
	naxe = v3(res.x, res.y, res.z);
	return (naxe);
}

t_vec3	quaternion_rotation_vec(t_vec3 a, t_vec3 b, double angle)
{
	t_vec4	qua_a;
	t_vec4	qua_b;
	t_vec4	res;
	t_vec3	naxe;

	qua_b.x = b.x * sin(angle / 2.);
	qua_b.y = b.y * sin(angle / 2.);
	qua_b.z = b.z * sin(angle / 2.);
	qua_b.w = cos(angle / 2.);
	qua_a.x = a.x;
	qua_a.y = a.y;
	qua_a.z = a.z;
	qua_a.w = 0.;
	res = v4_dot(v4_dot(qua_b, qua_a), v4_con(qua_b));
	naxe = v3(res.x, res.y, res.z);
	return (naxe);
}
