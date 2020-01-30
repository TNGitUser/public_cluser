/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pomme-de-terre-saute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:11:55 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/23 12:34:52 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_nhit	*create_void_region(t_nhit *prev
		, double start, double end)
{
	t_nhit	*void_region_xhfer;

	if (!(void_region_xhfer = malloc(sizeof(t_nhit))))
		error("Void region malloc failed");
	void_region_xhfer->dist_st = start;
	void_region_xhfer->dist_lt = end;
	if (prev)
		prev->next = void_region_xhfer;
	void_region_xhfer->next = NULL;
	return (void_region_xhfer);
}

void			free_void_region(t_scene *s)
{
	t_nhit *nxt;
	t_nhit *cur;

	cur = s->void_regions;
	if (!cur)
		return ;
	while (cur)
	{
		nxt = cur->next;
		if (cur)
			free(cur);
		cur = nxt;
	}
	s->void_regions = NULL;
}

static void		check_void_region(t_nhit *void_region, double h1, double h2
		, t_obj *obj)
{
	if (!void_region)
		error("No void region, call is uncalled for (I think)");
	if (void_region->dist_st != -1 && void_region->dist_lt != -1)
	{
		if (h1 >= void_region->dist_st && h1 <= void_region->dist_lt
				&& h2 > void_region->dist_lt && obj == void_region->obj)
			void_region->dist_lt = h2;
		else if (h1 >= 0.0 && h1 <= void_region->dist_st
				&& h2 >= void_region->dist_st && obj == void_region->obj)
			void_region->dist_st = h1;
		else
		{
			if (void_region->next)
				check_void_region(void_region->next, h1, h2, obj);
			else
				check_void_region(create_void_region(void_region, -1, -1), h1
						, h2, obj);
		}
	}
	else
	{
		void_region->dist_st = h1;
		void_region->dist_lt = h2;
		void_region->obj = obj;
	}
}

void			get_void_region(t_scene *s)
{
	int	i;

	i = -1;
	if (GRADE != 2)
		printf("\033[0;31mWARNING : Voided region are only working with GRADE\
				= 2 for the moment\033[0m\n");
	s->void_regions = create_void_region(NULL, -1, -1);
	while (++i < s->n_obj * GRADE)
	{
		if (s->hit.clt[i].neg == 1 && s->hit.clt[i].obj->typ == 0)
		{
			check_void_region(s->void_regions, s->hit.clt[i].t
					, s->hit.clt[i].t, s->hit.clt[i].obj);
		}
		else if (s->hit.clt[i].neg == 1 && s->hit.clt[i + 1].neg == 1)
		{
			if (s->hit.clt[i + 1].t > s->hit.clt[i].t)
				check_void_region(s->void_regions, s->hit.clt[i].t
						, s->hit.clt[i + 1].t, s->hit.clt[i].obj);
			else
				check_void_region(s->void_regions, s->hit.clt[i + 1].t
						, s->hit.clt[i].t, s->hit.clt[i].obj);
			i++;
		}
	}
}

int				is_voided(t_nhit *void_region, double dist)
{
	if (dist >= INFINITY - 1)
		return (1);
	while (void_region)
	{
		if (dist >= void_region->dist_st && dist <= void_region->dist_lt)
			return (0);
		void_region = void_region->next;
	}
	return (1);
}
