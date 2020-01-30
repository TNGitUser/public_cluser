/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:25:02 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:17:00 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	m44_ide(double m[4][4])
{
	m44(m);
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
	m[3][3] = 1;
}

void	m44_tra(double m[4][4], double mt[4][4])
{
	int	c[2];

	m44(mt);
	c[1] = -1;
	while (++c[1] < 4)
	{
		c[0] = -1;
		while (++c[0] < 4)
			mt[c[0]][c[1]] = m[c[1]][c[0]];
	}
}

double	m44_canrev(double m[4][4])
{
	double det;

	det = m44_det(m);
	return (det);
}

void	m44_inv(double m[4][4], double mi[4][4])
{
	int		c[2];
	double	cof;
	double	det;

	m44_ide(mi);
	if ((det = m44_canrev(m)) == 0)
		return ;
	c[1] = -1;
	while (++c[1] < 4)
	{
		c[0] = -1;
		while (++c[0] < 4)
		{
			cof = m44_cof(m, c[1], c[0]);
			mi[c[0]][c[1]] = cof / det;
		}
	}
}

void	m44d41(double m[4][4], double pm[4][1], double rm[4][1])
{
	int		y;

	y = -1;
	while (++y < 4)
	{
		rm[y][0] = m[y][0] * pm[0][0] + \
					m[y][1] * pm[1][0] + \
					m[y][2] * pm[2][0] + \
					m[y][3] * pm[3][0];
	}
}
