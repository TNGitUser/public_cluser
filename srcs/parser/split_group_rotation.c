/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_group_rotation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:01:58 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/13 11:10:48 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rotate_x(t_vec3 *org, double a)
{
	t_vec3 r;

	r.x = org->x;
	r.y = org->y * cos(a) - org->z * sin(a);
	r.z = org->y * sin(a) + org->z * cos(a);
	org->x = r.x;
	org->y = r.y;
	org->z = r.z;
}

void	rotate_y(t_vec3 *org, double a)
{
	t_vec3 r;

	r.x = org->x * cos(a) + org->z * sin(a);
	r.y = org->y;
	r.z = org->z * cos(a) - org->x * sin(a);
	org->x = r.x;
	org->y = r.y;
	org->z = r.z;
}

void	rotate_z(t_vec3 *org, double a)
{
	t_vec3 r;

	r.x = org->x * cos(a) - org->y * sin(a);
	r.y = org->x * sin(a) + org->y * cos(a);
	r.z = org->z;
	org->x = r.x;
	org->y = r.y;
	org->z = r.z;
}

void	rotate_xyz(t_vec3 *org, t_vec3 *rot)
{
	rotate_x(org, rot->x * (M_PI / 180));
	rotate_y(org, rot->y * (M_PI / 180));
	rotate_z(org, rot->z * (M_PI / 180));
}
