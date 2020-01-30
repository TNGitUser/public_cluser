/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloranaglyph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:00:13 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/09 19:04:56 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		color_nored(int clr)
{
	t_rgb	color;
	t_rgb	sp;

	color.r = (clr >> 16) & 0xff;
	color.g = (clr >> 8) & 0xff;
	color.b = clr & 0xff;
	sp.r = 0;
	sp.g = color.g;
	sp.b = color.b;
	return (((sp.r & 0x0ff) << 16) | ((sp.g & 0x0ff) << 8) | (sp.b & 0x0ff));
}

int		color_nocyan(int clr)
{
	t_rgb	color;
	t_rgb	sp;

	color.r = (clr >> 16) & 0xff;
	color.g = (clr >> 8) & 0xff;
	color.b = clr & 0xff;
	sp.r = color.r;
	sp.g = 0;
	sp.b = 0;
	return (((sp.r & 0x0ff) << 16) | ((sp.g & 0x0ff) << 8) | (sp.b & 0x0ff));
}

void	color_secondary_pix(t_scene *s, int x, int y)
{
	int pix;

	if (x >= 0 && y >= 0 && x < s->mlx.wid && y < s->mlx.hei)
	{
		pix = (x + (s->mlx.hei - 1 - y) * s->mlx.wid) << 2;
		*((int *)(s[0].mlx.sst + pix)) = s->pix.clr;
		*(unsigned char*)&s->mlx.sst[pix + 3] = 0;
	}
}
