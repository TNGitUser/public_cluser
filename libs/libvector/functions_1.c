/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 21:52:59 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/15 21:53:00 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec3	v3_ver(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;
	double	d;

	v = v3_dif(v2, v1);
	d = v3_len(v1, v2);
	return (v3_scd(v, d));
}

t_vec3	v3_nor(t_vec3 v1)
{
	double	d;

	d = sqrt(v3_dot(v1, v1));
	return (v3_scd(v1, d));
}

t_vec3	v3_scp(t_vec3 v1, double d)
{
	return (v3(v1.x * d, v1.y * d, v1.z * d));
}

t_vec3	v3_scd(t_vec3 v1, double d)
{
	return (v3(v1.x / d, v1.y / d, v1.z / d));
}

double	v3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
