/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:20:45 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/11 01:14:56 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

double	m22_det(double m[2][2])
{
	return ((m[0][0] * m[1][1]) - (m[0][1] * m[1][0]));
}

void	m33_sub(double m1[3][3], double m[2][2], int row, int cln)
{
	int	c[2];
	int	d[2];

	m22(m);
	if (row < 0 || row > 2 || cln < 0 || cln > 2)
		return ;
	c[1] = 0;
	d[1] = -1;
	while (++d[1] < 2)
	{
		if (c[1] == row)
			c[1]++;
		c[0] = 0;
		d[0] = -1;
		while (++d[0] < 2)
		{
			if (c[0] == cln)
				c[0]++;
			m[d[1]][d[0]] = m1[c[1]][c[0]];
			c[0]++;
		}
		c[1]++;
	}
}

double	m33_cof(double m1[3][3], int row, int cln)
{
	double m[2][2];
	double cofactor;

	m22(m);
	m33_sub(m1, m, row, cln);
	cofactor = m22_det(m);
	if (((row + cln) % 2) != 0)
		cofactor *= -1;
	return (cofactor);
}

double	m33_det(double m[3][3])
{
	double d[3];

	d[0] = m33_cof(m, 0, 0);
	d[1] = m33_cof(m, 0, 1);
	d[2] = m33_cof(m, 0, 2);
	return (m[0][0] * d[0] + m[0][1] * d[1] + m[0][2] * d[2]);
}
