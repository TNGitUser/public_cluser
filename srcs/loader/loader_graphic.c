/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_graphic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:53:45 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/23 12:37:52 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	update_start(t_scene *s, int percentage)
{
	if (percentage == 0)
		return ;
	if (s->mlx.loader_ptr)
		mlx_destroy_image(s->mlx.ptr, s->mlx.loader_ptr);
}

static void	update_end(t_scene *s, int percentage)
{
	if (percentage != 100)
		return ;
	if (s->mlx.loader_ptr)
		mlx_destroy_image(s->mlx.ptr, s->mlx.loader_ptr);
}

static void	update_progress_bar(t_scene *s, int percentage, int (*c1)[3]
		, int (*c2)[3])
{
	int	x;
	int	y;
	int	limx;
	int	limy;
	int	rgb[3];

	x = (s->mlx.wid / 2) - (LOADING_BAR_W / 2);
	limx = percentage == 0 ? 0 : x
		+ (LOADING_BAR_W * (float)((float)percentage / (float)100));
	while (x < limx)
	{
		y = s->mlx.hei / 2 - (LOADING_BAR_H / 2);
		limy = y + LOADING_BAR_H;
		compute_gradient(((float)(x - (s->mlx.wid / 2 - LOADING_BAR_W / 2))
					/ (float)LOADING_BAR_W), c1, c2, &rgb);
		while (y < limy)
		{
			s->mlx.loader_str[4 * (y * s->mlx.wid) + 4 * x] = (char)rgb[0];
			s->mlx.loader_str[4 * (y * s->mlx.wid) + 4 * x + 1] = (char)rgb[1];
			s->mlx.loader_str[4 * (y * s->mlx.wid) + 4 * x + 2] = (char)rgb[2];
			++y;
		}
		++x;
	}
}

static void	display_text(t_scene *s, int percentage)
{
	char	*per;
	char	*string;
	int		i;

	per = ft_itoa(percentage);
	if (!per)
		per = ft_strdup("X");
	string = ft_strnjoin("Loading ", per, "%");
	if (!string)
		string = ft_strdup("Loading X %");
	ft_memdel((void **)&per);
	i = ft_strlen(string) / 2;
	mlx_string_put(s->mlx.ptr, s->mlx.win, s->mlx.wid / 2 - i * 5,
			s->mlx.hei / 2 - 10, 0xffffff, string);
	ft_memdel((void **)&string);
}

void		update_visual(t_scene *s, int percentage)
{
	int	var[3];
	int	c1[3];
	int	c2[3];

	c1[0] = C1_R;
	c1[1] = C1_G;
	c1[2] = C1_B;
	c2[0] = C2_R;
	c2[1] = C2_G;
	c2[2] = C2_B;
	update_start(s, percentage);
	s->mlx.loader_ptr = mlx_new_image(s->mlx.ptr, s->mlx.wid, s->mlx.hei);
	s->mlx.loader_str = mlx_get_data_addr(s->mlx.loader_ptr, &(var[0])
			, &(var[1]), &(var[2]));
	update_progress_bar(s, percentage, &c1, &c2);
	mlx_put_image_to_window(s->mlx.ptr, s->mlx.win, s->mlx.loader_ptr, 0, 0);
	display_text(s, percentage);
	mlx_do_sync(s->mlx.ptr);
	update_end(s, percentage);
}
