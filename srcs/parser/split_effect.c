/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 17:09:43 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/30 15:49:12 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	countsplit_blur(t_scene *s, char *blur)
{
	char	*axe;
	char	*pow;

	if ((count_word(blur, "<axe>")) != 1)
		error("'axe' tag is mandatory for camera movement");
	if ((count_word(blur, "<intensity>")) != 1)
		error("'intensity' tag is mandatory for camera movement");
	if (!(axe = ft_strinstr(blur, "<axe>", "</axe>")))
		error("Problem with 'axe' tag in camera movement");
	if (!(pow = ft_strinstr(blur, "<intensity>", "</intensity>")))
		error("Problem with 'intensity' tag in camera movement");
	s->efc.blu[0] = assign_axe(axe);
	s->efc.blu[1] = assign_int(pow);
	ft_strdel(&axe);
	ft_strdel(&pow);
}

static void	countsplit_anaglyph(t_scene *s, char *blur)
{
	char	*offset;
	char	*focus;

	if ((count_word(blur, "<offset>")) != 1)
		error("'offset' tag is mandatory for anaglyph effect");
	if ((count_word(blur, "<focus>")) != 1)
		error("'focus' tag is mandatory for anaglyph effect");
	if (!(offset = ft_strinstr(blur, "<offset>", "</offset>")))
		error("Problem with 'offset' value of anaglyph tag");
	if (!(focus = ft_strinstr(blur, "<focus>", "</focus>")))
		error("Problem with 'focus' value of anaglyph tag");
	s->efc.gly[0] = assign_double(offset);
	s->efc.gly[1] = assign_double(focus);
	ft_strdel(&offset);
	ft_strdel(&focus);
}

static void	split_effects_tags(t_scene *s, char *effects)
{
	char	*eff[5];

	if ((eff[0] = ft_strinstr(effects, "<antialiasing>", "</antialiasing>")))
		s->efc.aa = assign_aa(eff[0]);
	if ((eff[1] = ft_strinstr(effects, "<celshading>", "</celshading>")))
		s->efc.toon = assign_onoff(eff[1]);
	if ((eff[2] = ft_strinstr(effects, "<globalblur>", "</globalblur>")))
		countsplit_blur(s, eff[2]);
	if ((eff[3] = ft_strinstr(effects, "<anaglyph>", "</anaglyph>")))
		countsplit_anaglyph(s, eff[3]);
	if ((eff[4] = ft_strinstr(effects, "<colormode>", "</colormode>")))
		s->efc.clrm = assign_colortype(eff[4]);
	ft_strarraydeln(eff, 5, 0);
}

void		prcss_effects_tags(t_scene *s, char *scene)
{
	char	*effects;

	if ((effects = ft_strinstr(scene, "<effects>", "</effects>")))
	{
		deep_count_effects(effects);
		split_effects_tags(s, effects);
	}
	ft_strdel(&effects);
}
