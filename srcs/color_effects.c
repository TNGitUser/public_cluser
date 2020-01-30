/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_effects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 21:31:17 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/15 21:31:20 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		color_sepia(int clr)
{
	t_rgb	color;
	t_rgb	sp;

	color.r = (clr >> 16) & 0xff;
	color.g = (clr >> 8) & 0xff;
	color.b = clr & 0xff;
	sp.r = color.r * 0.393 + color.g * 0.769 + color.b * 0.189;
	sp.g = color.r * 0.349 + color.g * 0.686 + color.b * 0.168;
	sp.b = color.r * 0.272 + color.g * 0.534 + color.b * 0.131;
	sp.r = sp.r > 255 ? 255 : sp.r;
	sp.g = sp.g > 255 ? 255 : sp.g;
	sp.b = sp.b > 255 ? 255 : sp.b;
	return (((sp.r & 0x0ff) << 16) | ((sp.g & 0x0ff) << 8) | (sp.b & 0x0ff));
}

int		color_grayscale(int clr)
{
	t_rgb	color;
	t_rgb	sp;
	int		average;

	color.r = (clr >> 16) & 0xff;
	color.g = (clr >> 8) & 0xff;
	color.b = clr & 0xff;
	average = (color.r + color.g + color.b) / 3.0;
	sp.r = average;
	sp.g = average;
	sp.b = average;
	sp.r = sp.r > 255 ? 255 : sp.r;
	sp.g = sp.g > 255 ? 255 : sp.g;
	sp.b = sp.b > 255 ? 255 : sp.b;
	return (((sp.r & 0x0ff) << 16) | ((sp.g & 0x0ff) << 8) | (sp.b & 0x0ff));
}

int		color_negative(int clr)
{
	t_rgb	color;
	t_rgb	sp;

	color.r = (clr >> 16) & 0xff;
	color.g = (clr >> 8) & 0xff;
	color.b = clr & 0xff;
	sp.r = 255 - color.r;
	sp.g = 255 - color.g;
	sp.b = 255 - color.b;
	return (((sp.r & 0x0ff) << 16) | ((sp.g & 0x0ff) << 8) | (sp.b & 0x0ff));
}
