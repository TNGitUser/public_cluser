/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:55:16 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/01 18:44:10 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

int		ft_fcmp(double a, double b)
{
	double	absolute;

	absolute = fabs(a - b);
	if (absolute < TLRNCE)
		return (1);
	return (0);
}

void	ft_vtom(t_vec3 v, double m[4][1])
{
	m[0][0] = v.x;
	m[1][0] = v.y;
	m[2][0] = v.z;
	m[3][0] = 0;
}

void	ft_ptom(t_vec3 p, double m[4][1])
{
	m[0][0] = p.x;
	m[1][0] = p.y;
	m[2][0] = p.z;
	m[3][0] = 1;
}
