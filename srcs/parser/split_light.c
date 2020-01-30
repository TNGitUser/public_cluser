/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 20:02:59 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/23 23:14:00 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	split_point_light(t_scene *s, char *light, int i)
{
	char	*position;

	deep_count_plight(light);
	s->lht[i].p = (t_plt*)ft_secmemalloc(sizeof(t_plt));
	if (!(position = ft_strinstr(light, "<position>", "</position>")))
		error("'position' tag is mandatory for point light");
	s->lht[i].p->pos = assign_vector(position);
	ft_strdel(&position);
	s->lht[i].typ = 1;
}

void	split_directional_light(t_scene *s, char *light, int i)
{
	char	*direction;

	deep_count_dlight(light);
	s->lht[i].d = (t_dlt*)ft_secmemalloc(sizeof(t_dlt));
	if (!(direction = ft_strinstr(light, "<direction>", "</direction>")))
		error("'direction' tag is mandatory for direction light");
	s->lht[i].d->dir = assign_vector(direction);
	ft_strdel(&direction);
	s->lht[i].typ = 2;
}

void	split_spot_light(t_scene *s, char *light, int i)
{
	char	*position;
	char	*direction;
	char	*angle;

	deep_count_slight(light);
	s->lht[i].s = (t_slt*)ft_secmemalloc(sizeof(t_slt));
	if (!(position = ft_strinstr(light, "<position>", "</position>")))
		error("'position' tag is mandatory for spot light");
	s->lht[i].s->pos = assign_vector(position);
	if (!(direction = ft_strinstr(light, "<direction>", "</direction>")))
		error("'direction' tag is mandatory for spot light");
	s->lht[i].s->dir = assign_vector(direction);
	if (!(angle = ft_strinstr(light, "<angle>", "</angle>")))
		error("'angle' tag is mandatory for spot light");
	s->lht[i].s->ang = assign_double(angle);
	ft_degtorad(&s->lht[i].s->ang);
	ft_strdel(&position);
	ft_strdel(&direction);
	ft_strdel(&angle);
	s->lht[i].typ = 3;
}

void	split_rectangle_light(t_scene *s, char *light, int i)
{
	char	*str[7];

	deep_count_rlight(light);
	s->n_wht += 2;
	obj_realloc(s, s->n_obj + s->n_wht - 2);
	s->lht[i].a = (t_alt*)ft_secmemalloc(sizeof(t_alt));
	str[0] = ft_strinstr(light, "<position>", "</position>");
	str[1] = ft_strinstr(light, "<udirection>", "</udirection>");
	str[2] = ft_strinstr(light, "<vdirection>", "</vdirection>");
	str[3] = ft_strinstr(light, "<udensity>", "</udensity>");
	str[4] = ft_strinstr(light, "<vdensity>", "</vdensity>");
	str[5] = ft_strinstr(light, "<invertdirection>", "</invertdirection>");
	s->lht[i].a->pos = assign_vector(str[0]);
	s->lht[i].a->u = assign_vector(str[1]);
	s->lht[i].a->v = assign_vector(str[2]);
	s->lht[i].a->q_u = assign_int(str[3]);
	s->lht[i].a->q_v = assign_int(str[4]);
	if ((s->lht[i].a->inv = assign_onoff(str[5])) == 0)
		s->lht[i].a->inv = -1;
	if (!str[0] || !str[1] || !str[2] || !str[3] || !str[4] || !str[5])
		error("Some mandatory tag for rectagle light is missing");
	str[6] = NULL;
	ft_strarraydeln(str, 6, 0);
	s->lht[i].typ = 4;
}
