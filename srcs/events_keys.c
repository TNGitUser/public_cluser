/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 17:15:47 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/29 16:25:10 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	anaglyph_loop(int k, t_scene *s)
{
	if (k == 30)
		s->efc.gly[1] += 0.05;
	else if (k == 42)
		s->efc.gly[1] -= 0.05;
	clean_scene(s);
	return (0);
}

static int	rotations_loop(int k, t_scene *s)
{
	if (s->mlx.button_alt == 1)
	{
		if (k == 123)
			s->cam.rot.z -= 10;
		else if (k == 124)
			s->cam.rot.z += 10;
		else
			return (0);
	}
	else
	{
		if (k == 123)
			s->cam.rot.y -= 10;
		else if (k == 124)
			s->cam.rot.y += 10;
		if (k == 126)
			s->cam.rot.x -= 10;
		else if (k == 125)
			s->cam.rot.x += 10;
	}
	clean_scene(s);
	return (0);
}

static int	glare_loop(t_scene *s)
{
	if (s->cam.glr.select == 0)
	{
		s->cam.glr.select = 1;
		init_camlight_data(s);
	}
	else if (s->cam.glr.select == 3)
		s->cam.glr.select = -2;
	else if (s->cam.glr.select == -2)
		s->cam.glr.select = 2;
	clean_scene(s);
	return (0);
}

/*
**	TIP : use ft_putnbr(k) in key_press_loop to identify key values
*/

int			key_press_loop(int k, t_scene *s)
{
	if (k == 53 || k == 65307)
		finish();
	if (k == 5)
		glare_loop(s);
	if (k == 1)
		saving_image_ppm(s);
	if (k == 261)
		s->mlx.button_alt = 1;
	if (s->efc.gly[0] == 0 && k >= 123 && k <= 126)
		rotations_loop(k, s);
	else if (s->efc.gly[0] != 0 && (k == 30 || k == 42))
		anaglyph_loop(k, s);
	return (0);
}

int			key_release_loop(int k, t_scene *s)
{
	if (k == 261)
		s->mlx.button_alt = 0;
	return (0);
}
