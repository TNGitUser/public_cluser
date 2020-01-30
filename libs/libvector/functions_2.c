/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 21:53:05 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/20 22:21:41 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec3	v3_cro(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

t_vec3	v3_neg(t_vec3 v1)
{
	return (v3_scp(v1, -1.));
}

double	v3_len(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	v = v3_dif(v2, v1);
	return (sqrt(v3_dot(v, v)));
}

double	v3_le2(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	v = v3_dif(v2, v1);
	return (v3_dot(v, v));
}

int		v3_cmp(t_vec3 v1, t_vec3 v2)
{
	if (v1.x != v2.x || v1.y != v2.y || v1.z != v2.z)
		return (0);
	else
		return (1);
}
