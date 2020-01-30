/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_group.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:16:01 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/16 11:52:37 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <parser.h>

static void	init_group_array(char *grp, char *cmm[], int id)
{
	cmm[0] = ft_strinstr(grp, "<position>", "</position>");
	cmm[1] = ft_strinstr(grp, "<rotation>", "</rotation>");
	cmm[2] = ft_strinstr(grp, "<translation>", "</translation>");
	cmm[3] = ft_itoa((id + 1) * -1);
	cmm[4] = NULL;
	if (cmm[0] == NULL || cmm[1] == NULL || cmm[2] == NULL)
		error("Problem with some 'group', mandatory field(s) missing");
}

/*
** TODO : Add rotation and group position to light
*/

static void	process_lo(t_scene *s, char *cpt, t_vec3 mod[2])
{
	while (ft_strstr(cpt, "<light>"))
	{
		s->var_light++;
		lights_cycle(s, cpt, s->var_light);
		split_group_light_dispatcher(s, &(s->lht[s->var_light]), mod);
	}
	while (ft_strstr(cpt, "<object>"))
	{
		s->var_obj++;
		objects_cycle(s, cpt, s->var_obj);
		s->obj[s->var_obj].rot = v3_add(mod[1], s->obj[s->var_obj].rot);
		rotate_xyz(&(s->obj[s->var_obj].pr->pos), &(s->obj[s->var_obj].rot));
		s->obj[s->var_obj].pr->pos = v3_add(mod[0], s->obj[s->var_obj].pr->pos);
	}
}

static void	process_component(t_scene *s, char *cpt, t_vec3 mod[2], int id)
{
	char	*group;

	while (ft_strstr(cpt, "<group>"))
	{
		group = ft_strinstr_unlimited(cpt, "<group>", "</group>");
		if (group)
			process_group(s, group, id, mod);
		far_unlimited(cpt, "<group>", "</group>", '$');
		ft_strdel(&group);
	}
	while (ft_strstr(cpt, "<mesh>"))
	{
		s->grp_mod[0] = mod[0];
		s->grp_mod[1] = mod[1];
		mesh_cycle(s, cpt);
	}
	process_lo(s, cpt, mod);
	s->grp_mod[0] = assign_vector("0,0,0");
	s->grp_mod[1] = assign_vector("0,0,0");
}

void		process_group(t_scene *s, char *group, int id, t_vec3 mod[2])
{
	char	*cmm[8];
	char	*cpt;
	t_vec3	pos;

	init_group_array(group, cmm, id);
	pos = assign_vector(cmm[0]);
	pos = v3_add(pos, assign_vector(cmm[2]));
	pos = v3_add(pos, mod[0]);
	if (!(cpt = ft_strinstr_unlimited(group, "<components>", "</components>")))
		error("Problem with some 'components' tag (empty or faulty)");
	process_component(s, cpt, (t_vec3[2]) { pos, v3_add(assign_vector(cmm[1])
				, mod[1]) }, id);
	ft_strarraydeln(cmm, 5, 0);
	ft_strdel(&cpt);
}

void		group_cycle(t_scene *s, char *scene)
{
	int		i;
	int		grp_n;
	char	*group;
	t_vec3	mod[2];

	if ((grp_n = count_word(scene, "<group>")) != count_word(scene, "</group>"))
		error("'group' tag overlap detected");
	i = 999999;
	while ((group = ft_strinstr_unlimited(scene, "<group>", "</group>")))
	{
		process_group(s, group, ++i, mod);
		far_unlimited(scene, "<group>", "</group>", '$');
		ft_strdel(&group);
		group = NULL;
	}
}
