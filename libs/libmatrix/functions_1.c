/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:57:53 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/11 01:12:21 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

int		m44_cmp(double m1[4][4], double m2[4][4])
{
	int	c[2];

	c[1] = -1;
	while (++c[1] < 4)
	{
		c[0] = -1;
		while (++c[0] < 4)
			if (ft_fcmp(m1[c[1]][c[0]], m2[c[1]][c[0]]) == 0)
				return (0);
	}
	return (1);
}

void	m44_dot(double m1[4][4], double m2[4][4], double md[4][4])
{
	int	c[2];

	m44(md);
	c[1] = -1;
	while (++c[1] < 4)
	{
		c[0] = -1;
		while (++c[0] < 4)
		{
			md[c[1]][c[0]] = m1[c[1]][0] * m2[0][c[0]] + \
							m1[c[1]][1] * m2[1][c[0]] + \
							m1[c[1]][2] * m2[2][c[0]] + \
							m1[c[1]][3] * m2[3][c[0]];
		}
	}
}

void	m41_prv(t_vec3 *v, double m[4][4], double mp[4][1])
{
	int		y;
	double	vm[4][1];

	vm[0][0] = v->x;
	vm[1][0] = v->y;
	vm[2][0] = v->z;
	vm[3][0] = 0;
	y = -1;
	while (++y < 4)
	{
		mp[y][0] = m[y][0] * vm[0][0] + \
					m[y][1] * vm[1][0] + \
					m[y][2] * vm[2][0] + \
					m[y][3] * vm[3][0];
	}
}

void	m41_prp(t_vec3 *p, double m[4][4], double mp[4][1])
{
	int		y;
	double	pm[4][1];

	pm[0][0] = p->x;
	pm[1][0] = p->y;
	pm[2][0] = p->z;
	pm[3][0] = 1;
	y = -1;
	while (++y < 4)
	{
		mp[y][0] = m[y][0] * pm[0][0] + \
					m[y][1] * pm[1][0] + \
					m[y][2] * pm[2][0] + \
					m[y][3] * pm[3][0];
	}
}

void	m41_prs(double s, double m[4][4], double mp[4][4])
{
	int	c[2];

	m44(mp);
	c[1] = -1;
	while (++c[1] < 4)
	{
		c[0] = -1;
		while (++c[0] < 4)
			mp[c[1]][c[0]] = m[c[1]][c[0]] * s;
	}
}
