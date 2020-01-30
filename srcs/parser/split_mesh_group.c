/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_group.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 16:36:20 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/13 11:12:05 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <parser.h>

static void	init_mesh_array(char *grp, char *cmm[], int id)
{
	cmm[0] = ft_strinstr(grp, "<type>", "</type>");
	cmm[1] = ft_strinstr(grp, "<color>", "</color>");
	cmm[2] = ft_strinstr(grp, "<shine>", "</shine>");
	cmm[3] = ft_strinstr(grp, "<motion>", "</motion>");
	cmm[4] = ft_strinstr(grp, "<translation>", "</translation>");
	cmm[5] = ft_strinstr(grp, "<rotation>", "</rotation>");
	cmm[6] = ft_itoa((id + 1) * -1);
	cmm[7] = NULL;
	if (!cmm[0] || !cmm[1])
		error("Some mandatory mesh tag is missing");
}

static void	process_mesh(t_scene *s, char *group, int *count, int id)
{
	int		i;
	int		j;
	char	*cmm[8];

	j = 0;
	i = -1;
	init_mesh_array(group, cmm, id);
	if ((j = count_word(group, "<part>")) != count_word(group, "</part>"))
		error("'part' tag of mesh block overlap detected");
	if (ft_strcmp(cmm[0], "triangle_mesh") == 0)
	{
		deep_precount_obj(group);
		while (++i < j)
			split_mesh_group(s, group, cmm, count);
	}
	else
		error("The mesh type doesn't exist");
	ft_strarraydeln(cmm, 8, 0);
}

void		mesh_cycle(t_scene *s, char *scene)
{
	int		i;
	int		grp_n;
	int		parts;
	char	*mesh;

	parts = 0;
	if ((grp_n = count_word(scene, "<mesh>")) != count_word(scene, "</mesh>"))
		error("'mesh' tag overlap detected");
	i = -1;
	while (++i < grp_n)
	{
		if (!(mesh = ft_strinstr(scene, "<mesh>", "</mesh>")))
			error("Problem with some 'mesh' tag");
		process_mesh(s, mesh, &parts, i);
		find_and_replace(scene, "<mesh>", "<proces>");
		ft_strdel(&mesh);
	}
}

/*
**	if (s->n_prt != parts)
**	error("Something gone wrong with mesh tag process");
*/
