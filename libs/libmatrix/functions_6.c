/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:56:26 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/16 13:39:15 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	m44_mov(double x, double y, double z, double m[4][4])
{
	m44_ide(m);
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
}

void	m44_sca(double x, double y, double z, double m[4][4])
{
	m44(m);
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	m[3][3] = 1.;
}

void	m44_she(t_she s, double m[4][4])
{
	m44_ide(m);
	m[0][1] = s.xy;
	m[0][2] = s.xz;
	m[1][0] = s.yx;
	m[1][2] = s.yz;
	m[2][0] = s.zx;
	m[2][1] = s.zy;
}
