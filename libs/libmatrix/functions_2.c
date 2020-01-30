/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:23:12 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/11 01:14:01 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	m44_sub(double m1[4][4], double m[3][3], int row, int cln)
{
	int	c[2];
	int	d[2];

	m33(m);
	if (row < 0 || row > 3 || cln < 0 || cln > 3)
		return ;
	c[1] = 0;
	d[1] = -1;
	while (++d[1] < 3)
	{
		if (c[1] == row)
			c[1]++;
		c[0] = 0;
		d[0] = -1;
		while (++d[0] < 3)
		{
			if (c[0] == cln)
				c[0]++;
			m[d[1]][d[0]] = m1[c[1]][c[0]];
			c[0]++;
		}
		c[1]++;
	}
}

double	m44_cof(double m1[4][4], int row, int cln)
{
	double m[3][3];
	double cofactor;

	m33(m);
	m44_sub(m1, m, row, cln);
	cofactor = m33_det(m);
	if (((row + cln) % 2) != 0)
		cofactor *= -1;
	return (cofactor);
}

double	m44_det(double m[4][4])
{
	double d[4];

	d[0] = m44_cof(m, 0, 0);
	d[1] = m44_cof(m, 0, 1);
	d[2] = m44_cof(m, 0, 2);
	d[3] = m44_cof(m, 0, 3);
	return (m[0][0] * d[0] + m[0][1] * d[1] + m[0][2] * d[2] + m[0][3] * d[3]);
}
