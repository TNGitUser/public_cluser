/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prmtrn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 02:48:47 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/16 14:10:17 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char	**init_trn_array(t_scene *s, char *obj, int i)
{
	char	**trn;

	trn = (char**)ft_secmemalloc(sizeof(char*) * 11);
	trn[0] = ft_strinstr(obj, "<vertex1>", "</vertex1>");
	trn[1] = ft_strinstr(obj, "<vertex2>", "</vertex2>");
	trn[2] = ft_strinstr(obj, "<vertex3>", "</vertex3>");
	trn[3] = ft_strinstr(obj, "<type>", "</type>");
	trn[4] = ft_strinstr(obj, "<color>", "</color>");
	trn[5] = ft_strinstr(obj, "<shine>", "</shine>");
	trn[6] = ft_strinstr(obj, "<motion>", "</motion>");
	trn[7] = ft_strinstr(obj, "<normal>", "</normal>");
	trn[8] = ft_strinstr(obj, "<translation>", "</translation>");
	trn[9] = ft_strinstr(obj, "<rotation>", "</rotation>");
	trn[10] = ft_strinstr(obj, "<negatif>", "</negatif>");
	if (!trn[0] || !trn[1] || !trn[2] || !trn[3] || !trn[4])
		error("Some mandatory triangle tag is missing");
	s->obj[i].tr = (t_trn*)ft_secmemalloc(sizeof(t_trn));
	return (trn);
}

void		split_triangle_tags(t_scene *s, char *obj, int i)
{
	char	**trn;

	trn = init_trn_array(s, obj, i);
	s->obj[i].tr->v0 = assign_vector(trn[0]);
	s->obj[i].tr->v1 = assign_vector(trn[1]);
	s->obj[i].tr->v2 = assign_vector(trn[2]);
	s->obj[i].typ = 5;
	s->obj[i].clr = assign_hex(trn[4]);
	s->obj[i].id = i - s->n_prt + 1;
	assign_bidouble(trn[5], &s->obj[i].shi[0], &s->obj[i].shi[1]);
	s->obj[i].blur = assign_vector(trn[6]);
	s->obj[i].dir = assign_vector(trn[7]);
	s->obj[i].tra = assign_vector(trn[8]);
	s->obj[i].rot = assign_vector(trn[9]);
	s->obj[i].neg = trn[10] ? assign_double(trn[10]) : 0;
	ft_strarraydeln(trn, 11, 1);
}

static char	**init_prm_array(t_scene *s, char *obj, int i)
{
	char	**elm;

	elm = (char**)ft_secmemalloc(sizeof(char*) * 10);
	elm[0] = ft_strinstr(obj, "<position>", "</position>");
	elm[1] = ft_strinstr(obj, "<direction>", "</direction>");
	elm[2] = ft_strinstr(obj, "<dimension>", "</dimension>");
	elm[3] = ft_strinstr(obj, "<type>", "</type>");
	elm[4] = ft_strinstr(obj, "<color>", "</color>");
	elm[5] = ft_strinstr(obj, "<shine>", "</shine>");
	elm[6] = ft_strinstr(obj, "<motion>", "</motion>");
	elm[7] = ft_strinstr(obj, "<translation>", "</translation>");
	elm[8] = ft_strinstr(obj, "<rotation>", "</rotation>");
	elm[9] = ft_strinstr(obj, "<negatif>", "</negatif>");
	if (!elm[0] || !elm[1] || !elm[2] || !elm[3] || !elm[4])
		error("Some mandatory object tag is missing");
	s->obj[i].pr = (t_prm*)ft_secmemalloc(sizeof(t_prm));
	return (elm);
}

void		split_primitive_tags(t_scene *s, char *obj, int i)
{
	char	**elm;

	elm = init_prm_array(s, obj, i);
	s->obj[i].id = i - s->n_prt + 1;
	s->obj[i].pr->pos = assign_vector(elm[0]);
	s->obj[i].dir = assign_vector(elm[1]);
	s->obj[i].typ = assign_chartype(elm[3]);
	s->obj[i].pr->dim = assign_double(elm[2]);
	if (s->obj[i].typ == 3)
	{
		ft_degtorad(&s->obj[i].pr->dim);
		s->obj[i].pr->dim = tan(s->obj[i].pr->dim / 2.);
	}
	s->obj[i].clr = assign_hex(elm[4]);
	assign_bidouble(elm[5], &s->obj[i].shi[0], &s->obj[i].shi[1]);
	s->obj[i].blur = assign_vector(elm[6]);
	s->obj[i].tra = assign_vector(elm[7]);
	s->obj[i].rot = assign_vector(elm[8]);
	s->obj[i].neg = elm[9] ? assign_double(elm[9]) : 0;
	ft_strarraydeln(elm, 10, 1);
}
