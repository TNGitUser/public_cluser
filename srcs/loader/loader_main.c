/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:47:00 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/20 16:26:41 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_array(int (*arr1)[THREAD], int (*arr2)[THREAD])
{
	int	i;

	i = 0;
	while (i < THREAD)
	{
		(*arr1)[i] = 0;
		(*arr2)[i] = 0;
		++i;
	}
}

static int	check_completion(t_scene *s, int (*thread_status)[THREAD])
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < THREAD)
	{
		if (s[i].done && !(*thread_status)[i])
			(*thread_status)[i] = 1;
		if (s[i++].done == 0)
			ret = 1;
	}
	return (ret);
}

static void	update_loop(int thread_status[THREAD], int thread_check[THREAD]
		, int *per, int add)
{
	int	thr;

	thr = 0;
	while (thr < THREAD)
	{
		if (thread_status[thr] != thread_check[thr])
		{
			thread_check[thr] = thread_status[thr];
			*per += add;
		}
		++thr;
	}
}

void		start_program(t_scene *s, int per, int oldper, int add)
{
	int			thread_status[THREAD];
	int			thread_check[THREAD];
	pthread_t	worker_chief;

	init_array(&thread_status, &thread_check);
	if (pthread_create(&(worker_chief), NULL, select_image_mode, (void *)s))
		error("Worker chief creation failed");
	while (check_completion(s, &thread_status))
	{
		update_loop(thread_status, thread_check, &per, add);
		if (oldper != per)
		{
			update_visual(s, (oldper = per));
			if (COMPLETION_DISPLAY)
				printf_completion(per);
		}
	}
	if (COMPLETION_DISPLAY)
		printf("Current completion percentage : \033[38;2;0;255;0m100%%\n");
	update_visual(s, 100);
	mlx_put_image_to_window(s->mlx.ptr, s->mlx.win, s->mlx.pim, 0, 0);
}
