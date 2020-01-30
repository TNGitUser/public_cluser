/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:56:16 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/05 18:23:46 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "icamera.h"

static void		reset_rotation_axes(t_scene *s, t_initcam *cam)
{
	s->cam.v = cam->v_axe;
	s->cam.u = cam->u_axe;
	s->cam.w = cam->w_axe;
}

static void		stereoscopy_rotations(t_scene *s, t_initcam *cam)
{
	if (s->efc.clrm == 10)
		s->cam.rot.y -= s->efc.gly[1];
	else
		s->cam.rot.y += s->efc.gly[1];
	ft_degtorad(&s->cam.rot.y);
	cam->u_axe = quaternion_rotation_y(s, cam->u_axe);
	cam->v_axe = quaternion_rotation_y(s, cam->v_axe);
	cam->w_axe = quaternion_rotation_y(s, cam->w_axe);
	s->cam.rot.y = 0;
	reset_rotation_axes(s, cam);
}

static void		cam_rotations(t_scene *s, t_initcam *cam)
{
	ft_degtorad(&s->cam.rot.x);
	cam->v_axe = quaternion_rotation_x(s, cam->v_axe);
	cam->u_axe = quaternion_rotation_x(s, cam->u_axe);
	cam->w_axe = quaternion_rotation_x(s, cam->w_axe);
	s->cam.rot.x = 0;
	reset_rotation_axes(s, cam);
	ft_degtorad(&s->cam.rot.y);
	cam->v_axe = quaternion_rotation_y(s, cam->v_axe);
	cam->u_axe = quaternion_rotation_y(s, cam->u_axe);
	cam->w_axe = quaternion_rotation_y(s, cam->w_axe);
	s->cam.rot.y = 0;
	reset_rotation_axes(s, cam);
	ft_degtorad(&s->cam.rot.z);
	cam->v_axe = quaternion_rotation_z(s, cam->v_axe);
	cam->u_axe = quaternion_rotation_z(s, cam->u_axe);
	cam->w_axe = quaternion_rotation_z(s, cam->w_axe);
	s->cam.rot.z = 0;
	reset_rotation_axes(s, cam);
	if (s->efc.clrm >= 10)
		stereoscopy_rotations(s, cam);
}

static void		transform_axes(t_scene *s, t_initcam *cam)
{
	t_vec3	axe;
	double	angle;
	double	mirrortrick;

	mirrortrick = 1.;
	if (s->cam.dir.z < 0)
		mirrortrick = -1.;
	s->cam.dir = v3_scp(s->cam.dir, mirrortrick);
	cam->v_axe = v3(1., 0, 0);
	cam->u_axe = v3(0, 1., 0);
	cam->w_axe = v3(0, 0, 1.);
	axe = (v3_snr(v3_cro(cam->w_axe, s->cam.dir)));
	angle = acos(v3_dot(s->cam.dir, cam->w_axe));
	cam->w_axe = s->cam.dir;
	cam->v_axe = quaternion_rotation_vec(cam->v_axe, axe, angle);
	cam->u_axe = quaternion_rotation_vec(cam->u_axe, axe, angle);
	if (mirrortrick == -1.)
	{
		cam->w_axe = v3_neg(cam->w_axe);
		cam->v_axe = v3_neg(cam->v_axe);
		s->cam.dir = v3_neg(s->cam.dir);
	}
	reset_rotation_axes(s, cam);
	s->cam.select = EXISTENT_AXES;
}

void			precalc_camera(t_scene *s)
{
	t_initcam	cam;

	if (s->cam.select == DEFAULT_AXES)
		transform_axes(s, &cam);
	else
	{
		cam.v_axe = s->cam.v;
		cam.u_axe = s->cam.u;
		cam.w_axe = s->cam.w;
	}
	cam_rotations(s, &cam);
	cam.h_wid = tan((s->cam.fov / (180. / M_PI)) / 2.);
	cam.h_hei = cam.h_wid * ((double)s->mlx.hei / (double)s->mlx.wid);
	s->cam.bottleft = v3_dif(cam.w_axe, v3_scp(cam.u_axe, cam.h_hei));
	s->cam.bottleft = v3_dif(s->cam.bottleft, v3_scp(cam.v_axe, cam.h_wid));
	s->cam.vi_x = v3_scd(v3_scp(v3_scp(cam.v_axe, 2.), cam.h_wid), s->mlx.wid);
	s->cam.vi_y = v3_scd(v3_scp(v3_scp(cam.u_axe, 2.), cam.h_hei), s->mlx.hei);
}
