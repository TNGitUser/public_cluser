/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   afterparser_imp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 20:45:35 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:13:44 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	blur_check(t_obj *o, int *blur)
{
	if (v3_cmp(v3(0, 0, 0), o->blur) == 0 && blur[0] != 0)
		error("Concurrently blur method in the scene");
}

static void	improve_lights(t_lht *l)
{
	if (l->pow < 0)
		error("Seriously? Black holes are not supported...");
	if (l->clr == 0)
		error("The color of the light cannot be 'black'");
	if (l->s && (l->s->ang > 360 || l->s->ang < 0))
		error("The angle of the some spot light is invalid [0 to 360]");
	l->pow *= 10.;
}

static void	improve_triangles(t_scene *s, int *i, int *blur)
{
	t_vec3	center;

	blur_check(&s->obj[*i], blur);
	if (s->obj[*i].id > 0)
	{
		obj_translation(&s->obj[*i]);
		center = v3_scd(v3_add(v3_add(s->obj[*i].tr->v0, s->obj[*i].tr->v1)
					, s->obj[*i].tr->v2), 3.);
		rotate_triangle(&s->obj[*i], &center);
	}
	else
		rotate_mesh(s, i);
}

static void	improve_primitives(t_obj *o, int *blur)
{
	if (v3_cmp(v3(0, 0, 0), o->dir) == 1)
		error("Invalid object direction detected");
	if (o->pr->dim < 0)
		error("The object dimension cannot be negative");
	blur_check(o, blur);
	o->dir = v3_nor(o->dir);
	obj_translation(o);
	add_transform_to_obj(o);
}

void		improve_data(t_scene *s)
{
	int i;
	int	blur_check[2];

	i = -1;
	while (++i < s->n_lht)
		improve_lights(&s->lht[i]);
	ft_bzero(&blur_check, sizeof(int) * 2);
	i = -1;
	if (s->efc.blu[0] != 0)
		blur_check[0] = 1;
	while (++i < s->n_obj)
	{
		if (s->obj[i].pr)
			improve_primitives(&s->obj[i], blur_check);
		else
			improve_triangles(s, &i, blur_check);
	}
	determinate_max_time(s);
}
