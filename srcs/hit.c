/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 18:25:35 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/23 12:31:41 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		get_object_hit(t_scene *s)
{
	int		i;

	i = -1;
	s->hit.t = INFINITY;
	while (++i < s->hit.n_clt)
	{
		if (s->hit.clt[i].t > 0 && s->hit.clt[i].t < s->hit.t
				&& is_voided(s->void_regions, s->hit.clt[i].t)
				&& s->hit.clt[i].obj->neg != 1)
		{
			s->hit.t = s->hit.clt[i].t;
			s->hit.obj = s->hit.clt[i].obj;
		}
	}
	s->hit.isc = find_intersection_point(s->hit.ray, &s->hit.t);
}

/*
**	TODO : Sort the clt array from here and not after
*/

void		collect_object_isc(t_scene *s, t_ray *r)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = -1;
	bzero(s->hit.clt, sizeof(t_clt) * s->n_obj * GRADE);
	while (++i < s->n_obj)
	{
		s->hit.tt[0] = 0;
		s->hit.tt[1] = 0;
		s->hit.tt[2] = 0;
		object_intersection(&s->obj[i], r, s->hit.tt);
		j = 0;
		while (s->hit.tt[j] != 0)
		{
			s->hit.clt[k].t = s->hit.tt[j];
			s->hit.clt[k].obj = &s->obj[i];
			s->hit.clt[k].neg = s->obj[i].neg;
			j++;
			k++;
		}
	}
	s->hit.n_clt = k;
	get_void_region(s);
}

void		get_shadow_hit(t_scene *s)
{
	int		i;

	i = -1;
	s->hit.t = INFINITY;
	while (++i < s->hit.n_clt)
	{
		if (s->hit.clt[i].t > BIAS && s->hit.clt[i].t < s->hit.t
				&& is_voided(s->void_regions, s->hit.clt[i].t)
				&& s->hit.clt[i].obj->neg != 1)
			s->hit.t = s->hit.clt[i].t;
	}
}

void		collect_shadow_isc(t_scene *s, t_ray *r)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = -1;
	bzero(s->hit.clt, sizeof(t_clt) * s->n_obj * GRADE);
	while (++i < s->n_obj)
	{
		s->hit.tt[0] = 0;
		s->hit.tt[1] = 0;
		s->hit.tt[2] = 0;
		shadow_intersection(&s->obj[i], r, s->hit.tt);
		j = 0;
		while (s->hit.tt[j] != 0)
		{
			s->hit.clt[k].t = s->hit.tt[j];
			s->hit.clt[k].obj = &s->obj[i];
			s->hit.clt[k].neg = s->obj[i].neg;
			j++;
			k++;
		}
	}
	s->hit.n_clt = k;
	get_void_region(s);
}

/*
** WARNING : Not used for the moment
*/

void		sort_collected_hit(t_scene *s)
{
	int		i;
	int		j;
	t_clt	temp;

	j = -1;
	while (++j + 1 < s->hit.n_clt)
	{
		i = -1;
		while (++i + 1 < s->hit.n_clt)
			if (s->hit.clt[i].t > s->hit.clt[i + 1].t)
			{
				temp = s->hit.clt[i];
				s->hit.clt[i] = s->hit.clt[i + 1];
				s->hit.clt[i + 1] = temp;
			}
	}
}
