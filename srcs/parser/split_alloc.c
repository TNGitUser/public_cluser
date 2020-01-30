/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:51:13 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/13 11:42:53 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		find_and_replace(char *str, char *find, char *replace)
{
	int	i;
	int	j;
	int k;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] == find[0])
		{
			j = 0;
			while (str[i] && find[j] && str[i] == find[j])
			{
				i++;
				j++;
			}
			i -= j;
			if (find[j] == '\0')
			{
				k = -1;
				while (++k < j)
					str[i + k] = replace[k];
				return ;
			}
		}
}

static void	presplit_light(t_scene *s, char *light, int i)
{
	char	*intensity;
	char	*color;

	if (!(intensity = ft_strinstr(light, "<intensity>", "</intensity>")))
		error("'intensity' tag of some light is missing");
	s->lht[i].pow = assign_double(intensity);
	if (!(color = ft_strinstr(light, "<color>", "</color>")))
		error("'color' tag of some light is missing");
	s->lht[i].clr = assign_hex(color);
	ft_strdel(&intensity);
	ft_strdel(&color);
}

void		lights_cycle(t_scene *s, char *scene, int i)
{
	char	*light;
	char	*type;

	if (!(light = ft_strinstr(scene, "<light>", "</light>")))
		error("Problem with some 'light' block");
	if (!(type = ft_strinstr(light, "<type>", "</type>")))
		error("'type' tag of some light is missing");
	deep_precount_lht(light);
	presplit_light(s, light, i);
	if (ft_strcmp(type, "point") == 0)
		split_point_light(s, light, i);
	else if (ft_strcmp(type, "directional") == 0)
		split_directional_light(s, light, i);
	else if (ft_strcmp(type, "spot") == 0)
		split_spot_light(s, light, i);
	else if (ft_strcmp(type, "rectangle") == 0)
		split_rectangle_light(s, light, i);
	else
		error("One or several wrong light type [ex: 'spot']");
	find_and_replace(scene, "<light>", "<prces>");
	ft_strdel(&light);
	ft_strdel(&type);
}

void		objects_cycle(t_scene *s, char *scene, int i)
{
	char	*object;
	char	*type;

	if (!(object = ft_strinstr(scene, "<object>", "</object>")))
		error("Problem with some 'object' tag");
	if (!(type = ft_strinstr(object, "<type>", "</type>")))
		error("'type' tag of some object is missing");
	deep_precount_obj(object);
	if (ft_strcmp(type, "triangle") == 0)
	{
		deep_count_triangle(object);
		split_triangle_tags(s, object, i);
	}
	else
	{
		deep_count_primitive(object);
		split_primitive_tags(s, object, i);
	}
	find_and_replace(scene, "<object>", "<proces>");
	ft_strdel(&object);
	ft_strdel(&type);
}

void		split_allocated_tags(t_scene *s, char *scene)
{
	s->n_obj += s->n_prt;
	s->obj = (t_obj*)ft_secmemalloc(sizeof(t_obj) * (s->n_obj + s->n_wht));
	s->lht = (t_lht*)ft_secmemalloc(sizeof(t_lht) * s->n_lht);
	s->var_obj = -1;
	s->var_light = -1;
	group_cycle(s, scene);
	while (++(s->var_light) < s->n_lht)
		lights_cycle(s, scene, s->var_light);
	mesh_cycle(s, scene);
	while (++(s->var_obj) < s->n_obj)
		objects_cycle(s, scene, s->var_obj);
	white_cycle(s);
	s->n_obj += s->n_wht;
}
