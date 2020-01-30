/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counttags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 02:27:08 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/22 17:17:31 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	check_root_structure(char *str)
{
	int		i;
	int		j;
	char	*scene;

	i = 0;
	i = -1;
	scene = "<scene>";
	while (++i < 7)
		if (str[i] != scene[i])
			error("All tag must be included in the root tag 'scene'");
	scene = "</scene>";
	i = ft_strlen(str);
	j = -1;
	while (++j < 8)
	{
		if (str[i - 8 + j] != scene[j])
			error("All tag must be included in the root tag 'scene'");
	}
}

static void	count_cam_win_eff(char *tmp)
{
	int i[3];

	if ((i[0] = count_word(tmp, "<camera>")) != count_word(tmp, "</camera>"))
		error("'camera' tag overlap detected");
	if ((i[1] = count_word(tmp, "<window>")) != count_word(tmp, "</window>"))
		error("'window' tag overlap detected");
	if ((i[2] = count_word(tmp, "<effects>")) != count_word(tmp, "</effects>"))
		error("'effects' tag overlap detected");
	if (i[0] != 1)
		error("'camera' block missing or duplicated");
	if (i[1] != 1)
		error("'window' block missing or duplicated");
	if (i[2] > 1)
		error("'effects' block is duplicated");
}

static void	count_light_object(t_scene *s, char *temp)
{
	int i;

	i = 0;
	if ((i = count_word(temp, "<light>")) != count_word(temp, "</light>"))
		error("'light' tag overlap detected");
	s->n_lht = i;
	if ((i = count_word(temp, "<object>")) != count_word(temp, "</object>"))
		error("'object' tag overlap detected");
	s->n_obj = i;
	if ((i = count_word(temp, "<part>")) != count_word(temp, "</part>"))
		error("'part' tag of grouped object overlap detected");
	s->n_prt = i;
}

void		count_tags(t_scene *s, char *str)
{
	char	*temp;
	int		i;

	i = count_tag_size(str);
	check_root_structure(str + i);
	if ((i = count_word(str, "<scene>")) != count_word(str, "</scene>"))
		error("'scene' tag overlap detected");
	if (!(temp = ft_strinstr(str + i, "<scene>", "</scene>")))
		error("Missing 'scene' tag");
	count_cam_win_eff(temp);
	count_light_object(s, temp);
	ft_strdel(&temp);
}
