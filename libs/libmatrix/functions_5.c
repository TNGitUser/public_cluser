/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:29:23 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/02 01:21:25 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	m44_rtx(double ang, double m[4][4])
{
	double r;

	r = ang / 180. * M_PI;
	m44(m);
	m[0][0] = 1;
	m[1][1] = cos(r);
	m[1][2] = -sin(r);
	m[2][1] = sin(r);
	m[2][2] = cos(r);
	m[3][3] = 1;
}

void	m44_rty(double ang, double m[4][4])
{
	double r;

	r = ang / 180. * M_PI;
	m44(m);
	m[0][0] = cos(r);
	m[0][2] = sin(r);
	m[1][1] = 1;
	m[2][0] = -sin(r);
	m[2][2] = cos(r);
	m[3][3] = 1;
}

void	m44_rtz(double ang, double m[4][4])
{
	double r;

	r = ang / 180. * M_PI;
	m44(m);
	m[0][0] = cos(r);
	m[0][1] = -sin(r);
	m[1][0] = sin(r);
	m[1][1] = cos(r);
	m[2][2] = 1;
	m[3][3] = 1;
}

void	m44_rtv(t_vec3 a, t_vec3 b, double m[4][4])
{
	double	angle;
	double	ancos;
	double	ansin;
	t_vec3	axe;

	m44_ide(m);
	angle = acos(v3_dot(a, b));
	axe = v3_snr(v3_cro(a, b));
	ancos = cos(angle);
	ansin = sin(angle);
	m[0][0] = ancos + axe.x * axe.x * (1. - ancos);
	m[0][1] = axe.z * ansin + axe.y * axe.x * (1. - ancos);
	m[0][2] = -axe.y * ansin + axe.z * axe.x * (1. - ancos);
	m[1][0] = -axe.z * ansin + axe.x * axe.y * (1. - ancos);
	m[1][1] = ancos + axe.y * axe.y * (1. - ancos);
	m[1][2] = axe.x * ansin + axe.z * axe.y * (1. - ancos);
	m[2][0] = axe.y * ansin + axe.x * axe.z * (1. - ancos);
	m[2][1] = -axe.x * ansin + axe.y * axe.z * (1. - ancos);
	m[2][2] = ancos + axe.z * axe.z * (1. - ancos);
}
