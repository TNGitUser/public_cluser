/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deepcountb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 01:54:53 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/11 21:15:27 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	deep_count_plight(char *light)
{
	if (count_word(light, "<position>") != 1)
		error("'position' tag is missing or doubled for point light");
}

void	deep_count_dlight(char *light)
{
	if (count_word(light, "<direction>") != 1)
		error("'direction' tag is missing or doubled for directional light");
}

void	deep_count_slight(char *light)
{
	if (count_word(light, "<position>") != 1)
		error("'position' tag is missing or doubled for spot light");
	else if (count_word(light, "<direction>") != 1)
		error("'direction' tag is missing or doubled for spot light");
	else if (count_word(light, "<angle>") != 1)
		error("'angle' tag is missing or doubled for spot light");
}

void	deep_precount_lht(char *light)
{
	if (count_word(light, "<intensity>") != 1)
		error("'intensity' tag is missing or doubled for light");
	else if (count_word(light, "<color>") != 1)
		error("'color' tag is missing or doubled for light");
	else if (count_word(light, "<type>") != 1)
		error("'type' tag is missing or doubled for light");
}

void	deep_count_rlight(char *light)
{
	if (count_word(light, "<position>") != 1)
		error("'position' tag is missing or doubled for rectangle light");
	else if (count_word(light, "<udirection>") != 1)
		error("'udirection' tag is missing or doubled for rectangle light");
	else if (count_word(light, "<vdirection>") != 1)
		error("'vdirection' tag is missing or doubled for rectangle light");
	else if (count_word(light, "<udensity>") != 1)
		error("'udensity' tag is missing or doubled for rectangle light");
	else if (count_word(light, "<vdensity>") != 1)
		error("'vdensity' tag is missing or doubled for rectangle light");
	else if (count_word(light, "<invertdirection>") != 1)
		error("'invertdirection' tag absent or doubled for rectangle light");
}
