/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:13:07 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/11 01:16:14 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "../libvector/vec.h"
# include <stdio.h>

# define TLRNCE 1e-3

typedef struct	s_she
{
	double		xy;
	double		xz;
	double		yx;
	double		yz;
	double		zx;
	double		zy;
}				t_she;

void			m44_print(double m[4][4]);
void			m33_print(double m[3][3]);
void			m41_print(double m[4][1]);

int				ft_fcmp(double a, double b);
void			ft_vtom(t_vec3 v, double m[4][1]);
void			ft_ptom(t_vec3 p, double m[4][1]);
void			m22(double m[2][2]);
double			m22_det(double m[2][2]);
void			m33(double m[3][3]);
double			m33_det(double m[3][3]);
double			m33_cof(double m1[3][3], int row, int cln);
void			m33_sub(double m1[3][3], double m[2][2], int row, int cln);
void			m41(double m[4][1]);
void			m44d41(double m[4][4], double pm[4][1], double rm[4][1]);
void			m44(double m[4][4]);
double			m44_det(double m1[4][4]);
double			m44_cof(double m1[4][4], int row, int cln);
int				m44_cmp(double m1[4][4], double m2[4][4]);
void			m44_ide(double m[4][4]);
void			m44_tra(double m[4][4], double mt[4][4]);
void			m44_dot(double m1[4][4], double m2[4][4], double md[4][4]);
void			m44_sub(double m1[4][4], double m[3][3], int row, int cln);
double			m44_canrev(double m[4][4]);
void			m44_inv(double m[4][4], double mi[4][4]);
void			m41_prp(t_vec3 *p, double m[4][4], double mp[4][1]);
void			m41_prv(t_vec3 *v, double m[4][4], double mv[4][1]);
void			m44_prs(double s, double m[4][4], double ms[4][4]);
void			m44_mov(double x, double y, double z, double m[4][4]);
void			m44_sca(double x, double y, double z, double m[4][4]);
void			m44_she(t_she she, double m[4][4]);
void			m44_rtx(double ang, double m[4][4]);
void			m44_rty(double ang, double m[4][4]);
void			m44_rtz(double ang, double m[4][4]);
void			m44_rtv(t_vec3 a, t_vec3 b, double m[4][4]);

#endif
