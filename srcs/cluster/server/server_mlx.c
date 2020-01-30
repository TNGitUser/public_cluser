/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 10:43:22 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/30 14:06:26 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	server_init_mlx(void *sv)
{
	t_scene *s;

	s = (t_scene *)sv;
	s->mlx.ptr = mlx_init();
	s->mlx.win = mlx_new_window(s->mlx.ptr, s->mlx.wid, s->mlx.hei
			, s->mlx.title);
	s->mlx.loader_ptr = mlx_new_image(s->mlx.ptr, s->mlx.wid, s->mlx.hei);
	s->mlx.loader_str = mlx_get_data_addr(s->mlx.loader_ptr, &s->mlx.b
			, &s->mlx.s
			, &s->mlx.e);
}

void	server_loop_mlx(void *sv)
{
	t_scene *s;

	s = (t_scene *)sv;
	mlx_put_image_to_window(s->mlx.ptr, s->mlx.win, s->mlx.loader_ptr, 0, 0);
	mlx_hook(s->mlx.win, 2, 0, key_press_loop, &s[0]);
	mlx_hook(s->mlx.win, 3, 0, key_release_loop, &s[0]);
	mlx_hook(s->mlx.win, 4, 0, mouse_loop, &s[0]);
	mlx_hook(s->mlx.win, 17, 0, finish, NULL);
	mlx_loop(s->mlx.ptr);
}
