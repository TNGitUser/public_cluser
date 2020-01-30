/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:52:33 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/30 11:48:42 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		clean_scene(t_scene *s)
{
	ft_bzero(s->mlx.pst, s->mlx.wid * s->mlx.hei * 4);
	if (s->cam.glr.select > 0)
	{
		ft_bzero(s->cam.glr.shadow, sizeof(int) * s->n_lht);
		s->cam.glr.select = 2;
	}
	if (s->efc.gly[0] != 0)
	{
		ft_bzero(s->mlx.sst, s->mlx.wid * s->mlx.hei * 4);
		s->efc.clrm = 10;
	}
	select_image_mode(s);
}

void		*select_image_mode(void *sv)
{
	static int	i;
	t_scene		*s;

	s = (t_scene *)sv;
	if (s->efc.gly[0] == 0)
		multithr_single_image(s);
	else
	{
		if (i == 0)
		{
			s->mlx.sim = mlx_new_image(s->mlx.ptr, s->mlx.wid, s->mlx.hei);
			s->mlx.sst = mlx_get_data_addr(s->mlx.sim, &s->mlx.b, &s->mlx.s,\
					&s->mlx.e);
			i = 1;
		}
		anaglyph_multi_image(s);
	}
	return (NULL);
}

static void	duplicate_scene_thread(t_scene *s)
{
	int i;
	int	add;

	i = 0;
	if (s->info.type != STANDALONE)
		add = (s->max_y - s->min_y) / THREAD;
	else
		add = s->mlx.hei / THREAD;
	s[i].strt = add * i + s->min_y;
	s[i].hit.clt = (t_clt*)ft_secmemalloc(sizeof(t_clt) * (s[i].n_obj * GRADE));
	while (++i < THREAD)
	{
		s[i] = s[0];
		s[i].id = i;
		s[i].done = 0;
		s[i].strt = add * i + s->min_y;
		s[i].hit.clt = (t_clt*)ft_secmemalloc(sizeof(t_clt)\
				* (s[i].n_obj * GRADE));
		s[i].obj = (t_obj*)ft_secmemalloc(sizeof(t_obj) * s->n_obj);
		ft_memcpy(s[i].obj, s[0].obj, sizeof(t_obj) * s->n_obj);
	}
}

/*
**	CLUSTER \ OK : Need to check args in main.c to determine if server or client
**			or standalone.
*/

int			main(int ac, char **av)
{
	t_scene	s[THREAD];

	ft_bzero((void *)&s, sizeof(t_scene) * THREAD);
	check_options(av, ac, &s[0]);
	if (s[0].info.type == CLIENT)
		cluster_client(&s[0]);
	else
		parse(&s[0], av[ac - 1], &ac, NULL);
	after_parser(&s[0], av[ac -1]);
	s->mlx.ptr = mlx_init();
	s->mlx.win = mlx_new_window(s->mlx.ptr, s->mlx.wid, s->mlx.hei,\
			s->mlx.title);
	s->mlx.pim = mlx_new_image(s->mlx.ptr, s->mlx.wid, s->mlx.hei);
	s->mlx.pst = mlx_get_data_addr(s->mlx.pim, &s->mlx.b, &s->mlx.s, &s->mlx.e);
	duplicate_scene_thread(s);
	start_program(s, 0, -1, 100 / THREAD);
	mlx_key_hook(s->mlx.win, key_press_loop, &s[0]);
	mlx_hook(s->mlx.win, 2, 0, key_press_loop, &s[0]);
	mlx_hook(s->mlx.win, 3, 0, key_release_loop, &s[0]);
	mlx_hook(s->mlx.win, 4, 0, mouse_loop, &s[0]);
	mlx_hook(s->mlx.win, 17, 0, finish, NULL);
	mlx_loop(s->mlx.ptr);
	return (0);
}
