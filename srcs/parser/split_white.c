/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_white.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 04:13:08 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/14 13:16:40 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj	create_f_triangle(t_lht rl, int i)
{
	t_obj	t;

	ft_bzero((void*)&t, sizeof(t_obj));
	t.typ = 5;
	t.id = ID_OFFSET + i;
	t.clr = rl.clr;
	t.tr = (t_trn*)ft_secmemalloc(sizeof(t_trn));
	t.tr->v0 = rl.a->pos;
	t.tr->v1 = v3_add(rl.a->pos, rl.a->v);
	t.tr->v2 = v3_add(rl.a->pos, rl.a->u);
	return (t);
}

t_obj	create_s_triangle(t_lht rl, int i)
{
	t_obj	t;

	ft_bzero((void*)&t, sizeof(t_obj));
	t.typ = 5;
	t.id = ID_OFFSET + i;
	t.clr = rl.clr;
	t.tr = (t_trn*)ft_secmemalloc(sizeof(t_trn));
	t.tr->v0 = v3_add(rl.a->pos, rl.a->u);
	t.tr->v0 = v3_add(t.tr->v0, rl.a->v);
	t.tr->v1 = v3_add(rl.a->pos, rl.a->v);
	t.tr->v2 = v3_add(rl.a->pos, rl.a->u);
	return (t);
}

void	triangles(t_scene *s, t_lht *l, int i)
{
	s->obj[s->n_obj + i] = create_f_triangle(*l, i);
	s->obj[s->n_obj + i + 1] = create_s_triangle(*l, i);
}

void	white_cycle(t_scene *s)
{
	int i;
	int	n;

	n = -1;
	i = 0;
	while (++n < s->n_lht)
	{
		if (s->lht[n].typ == 4)
		{
			triangles(s, &s->lht[n], i);
			i += 2;
		}
	}
}
