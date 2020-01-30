/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 22:03:28 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:03:50 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vec3	mix_light(t_vec3 light[], double en[], double *t_en, int *n)
{
	t_vec3	total;
	double	rate;
	int		i;

	total = v3(0, 0, 0);
	if (*t_en == 0)
		return (total);
	i = -1;
	while (++i < *n)
	{
		rate = en[i] / *t_en;
		total = v3_add(total, v3_scp(light[i], rate));
	}
	return (total);
}

static t_vec3	mix_color(t_vec3 color, t_vec3 light_clr, double *en)
{
	t_vec3	mov;

	mov = v3_dif(light_clr, color);
	ft_fmax(en, 1.);
	mov = v3_scp(mov, *en);
	return (v3_add(color, mov));
}

int				get_color(t_scene *s, double en[], int clr, double amb)
{
	int		i;
	double	total_en;
	t_vec3	v_clr;
	t_vec3	l_clr;
	t_vec3	l_array[s->n_lht];

	v_clr = v3((clr >> 16) & 0xFF, (clr >> 8) & 0xFF, (clr & 0xFF));
	v_clr = v3_scp(v_clr, amb);
	total_en = 0;
	i = -1;
	while (++i < s->n_lht)
	{
		l_array[i] = v3((s->lht[i].clr >> 16) & 0xFF, \
			(s->lht[i].clr >> 8) & 0xFF, s->lht[i].clr & 0xFF);
		total_en += en[i];
	}
	l_clr = mix_light(l_array, en, &total_en, &i);
	v_clr = mix_color(v_clr, l_clr, &total_en);
	ft_fmax(&v_clr.x, 255.);
	ft_fmax(&v_clr.y, 255.);
	ft_fmax(&v_clr.z, 255.);
	return (((int)v_clr.x << 16) | ((int)v_clr.y << 8) | (int)v_clr.z);
}
