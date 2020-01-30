/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deepcount.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 01:54:46 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/30 15:45:27 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	deep_count_camera_windows(char *camera, char *window)
{
	if (count_word(camera, "<position>") != 1)
		error("'position' tag of camera is missing or doubled");
	else if (count_word(camera, "<direction>") != 1)
		error("'direction' tag of camera is missing or doubled");
	else if (count_word(camera, "<fov>") != 1)
		error("'fov' tag of camera is missing or doubled");
	else if (count_word(camera, "<rotation>") > 1)
		error("'rotation' tag of camera is doubled");
	else if (count_word(camera, "<glare>") > 1)
		error("'glare' tag of camera is doubled");
	else if (count_word(window, "<title>") != 1)
		error("'title' tag of window is missing or doubled");
	else if (count_word(window, "<dimension>") != 1)
		error("'dimension' tag of window is missing or doubled");
	else if (count_word(window, "<ambient>") != 1)
		error("'ambient' tag of window is missing or doubled");
}

void	deep_count_effects(char *effects)
{
	if ((count_word(effects, "<antialiasing>")) > 1)
		error("'antialiasing' tag of effects is doubled");
	if ((count_word(effects, "<celshading>")) > 1)
		error("'celshading' tag of effects is doubled");
	if ((count_word(effects, "<globalblur>")) > 1)
		error("'globalblur' tag of effects is doubled");
	if ((count_word(effects, "<anaglyph>")) > 1)
		error("'anaglyph' tag of effects is doubled");
	if ((count_word(effects, "<colormode>")) > 1)
		error("'colormode' tag of effects is doubled");
}

void	deep_count_primitive(char *object)
{
	if (count_word(object, "<position>") != 1)
		error("'position' tag of object is missing or doubled");
	else if (count_word(object, "<direction>") != 1)
		error("'direction' tag of object is missing or doubled");
	else if (count_word(object, "<dimension>") != 1)
		error("'dimension' tag of object is missing or doubled");
}

void	deep_count_triangle(char *object)
{
	if (count_word(object, "<vertex1>") != 1)
		error("'vertex1' tag of triangle/mesh is missing or doubled");
	else if (count_word(object, "<vertex2>") != 1)
		error("'vertex2' tag of triangle/mesh is missing or doubled");
	else if (count_word(object, "<vertex3>") != 1)
		error("'vertex3' tag of triangle/mesh is missing or doubled");
}

void	deep_precount_obj(char *object)
{
	if (count_word(object, "<type>") != 1)
		error("'type' tag of object/group is missing or doubled");
	else if (count_word(object, "<direction>") > 1)
		error("'direction' tag of object is doubled");
	else if (count_word(object, "<color>") != 1)
		error("'color' tag of object/group is missing or doubled");
	else if (count_word(object, "<shine>") > 1)
		error("'shine' tag of object/group is doubled");
	else if (count_word(object, "<motion>") > 1)
		error("'motion' tag of object/group is doubled");
	else if (count_word(object, "<translation>") > 1)
		error("'translation' tag of object/group is doubled");
	else if (count_word(object, "<rotation>") > 1)
		error("'rotation' tag of object/group is doubled");
}
