/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mesh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 16:36:20 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/13 11:19:25 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <parser.h>

static void	rotate_mesh_trn(t_scene *s, t_obj *obj)
{
	rotate_xyz(&(obj->tr->v0), &(s->grp_mod[1]));
	rotate_xyz(&(obj->tr->v1), &(s->grp_mod[1]));
	rotate_xyz(&(obj->tr->v2), &(s->grp_mod[1]));
	obj->tr->v0 = v3_add(obj->tr->v0, s->grp_mod[0]);
	obj->tr->v1 = v3_add(obj->tr->v1, s->grp_mod[0]);
	obj->tr->v2 = v3_add(obj->tr->v2, s->grp_mod[0]);
}

void		split_mesh_part(t_scene *s, char *part, char *cmm[], int *count)
{
	char	*mesh[3];

	s->var_obj++;
	mesh[0] = ft_strinstr(part, "<vertex1>", "</vertex1>");
	mesh[1] = ft_strinstr(part, "<vertex2>", "</vertex2>");
	mesh[2] = ft_strinstr(part, "<vertex3>", "</vertex3>");
	s->obj[s->var_obj].tr = (t_trn*)ft_secmemalloc(sizeof(t_trn));
	s->obj[s->var_obj].tr->v0 = assign_vector(mesh[0]);
	s->obj[s->var_obj].tr->v1 = assign_vector(mesh[1]);
	s->obj[s->var_obj].tr->v2 = assign_vector(mesh[2]);
	s->obj[s->var_obj].typ = 5;
	s->obj[s->var_obj].clr = assign_hex(cmm[1]);
	assign_bidouble(cmm[2], &s->obj[s->var_obj].shi[0]
			, &s->obj[s->var_obj].shi[1]);
	s->obj[s->var_obj].blur = assign_vector(cmm[3]);
	s->obj[s->var_obj].tra = assign_vector(cmm[4]);
	s->obj[s->var_obj].rot = v3_add(assign_vector(cmm[5]), s->grp_mod[1]);
	s->obj[s->var_obj].id = assign_int(cmm[6]);
	rotate_mesh_trn(s, &(s->obj[s->var_obj]));
	ft_strarraydeln(mesh, 3, 0);
	(*count)++;
}

void		split_mesh_group(t_scene *s, char *group, char *cmm[], int *count)
{
	char	*part;

	if (!(part = ft_strinstr(group, "<part>", "</part>")))
		error("No 'part' tag in mesh block was found");
	deep_count_triangle(part);
	split_mesh_part(s, part, cmm, count);
	find_and_replace(group, "<part>", "<proces>");
	ft_strdel(&part);
}
