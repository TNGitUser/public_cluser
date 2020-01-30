/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:19:21 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/27 22:37:07 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec4	v4(double x, double y, double z, double w)
{
	t_vec4	q;

	q.x = x;
	q.y = y;
	q.z = z;
	q.w = w;
	return (q);
}

double	v4_len(t_vec4 q)
{
	double	d;

	d = (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w);
	return (sqrt(d));
}

t_vec4	v4_nor(t_vec4 q)
{
	double l;

	l = v4_len(q);
	q.x = q.x / l;
	q.y = q.y / l;
	q.z = q.z / l;
	q.w = q.w / l;
	return (q);
}

t_vec4	v4_con(t_vec4 q)
{
	t_vec4	q2;

	q2.x = -q.x;
	q2.y = -q.y;
	q2.z = -q.z;
	q2.w = q.w;
	return (q2);
}

t_vec4	v4_dot(t_vec4 q1, t_vec4 q2)
{
	t_vec4	q;

	q.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	q.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	q.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	q.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	return (q);
}
