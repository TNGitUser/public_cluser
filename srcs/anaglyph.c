/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anaglyph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:51:13 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/05 18:16:48 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "icamera.h"

void	sum_array_color(t_scene *s)
{
	unsigned long i;
	unsigned long l;

	i = -1;
	l = s->mlx.hei * s->mlx.wid * 4;
	while (++i < l)
	{
		s->mlx.pst[i] += s->mlx.sst[i];
		if (*(unsigned char*)&s->mlx.pst[i] > 255)
			*(unsigned char*)&s->mlx.pst[i] = 255;
	}
}

void	anaglyph_multi_image(t_scene *s)
{
	s->cam = s->rstcam;
	s->efc.clrm = 10;
	multithr_single_image(s);
	s->efc.clrm = 11;
	s->cam = s->rstcam;
	multithr_single_image(s);
	sum_array_color(s);
}
