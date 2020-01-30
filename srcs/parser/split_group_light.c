/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_group_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 10:51:08 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/16 13:14:21 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	apply_mod(t_scene *s, t_vec3 *pos, t_vec3 mod[2], t_lht *light)
{
	(void)s;
	if (pos)
	{
		rotate_xyz(pos, &(mod[1]));
		*pos = v3_add(mod[0], *pos);
	}
	if (light->typ == L_DIR || light->typ == L_SPOT)
		rotate_xyz(light->typ == L_DIR ? &(light->d->dir) : &(light->s->dir)
				, &(mod[1]));
	if (light->typ == L_RECT)
	{
		rotate_xyz(&(light->a->u), &(mod[1]));
		rotate_xyz(&(light->a->v), &(mod[1]));
	}
}

void		split_group_light_dispatcher(t_scene *s, t_lht *light
		, t_vec3 mod[2])
{
	if (light->typ == L_POINT)
		apply_mod(s, &(light->p->pos), mod, light);
	else if (light->typ == L_DIR)
		apply_mod(s, NULL, mod, light);
	else if (light->typ == L_SPOT)
		apply_mod(s, &(light->s->pos), mod, light);
	else if (light->typ == L_RECT)
		apply_mod(s, &(light->a->pos), mod, light);
}
