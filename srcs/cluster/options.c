/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:22:15 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/28 15:00:34 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_cluster_bds(t_scene *s)
{
	s->min_y = 0;
	s->max_y = 0;
}

void	check_options(char **av, int ac, t_scene *s)
{
	init_cluster_bds(s);
	if (ac < 2 || ac > 3)
		error("Usage: ./RT [-[s|c]] [scene.xml]");
	if (ac == 2 && (!ft_strcmp(av[1], "-s") || !ft_strcmp(av[1], "-c")))
	{
		if (!ft_strcmp(av[1], "-s"))
			error("Usage: ./RT -s [scene.xml]");
		else
			s->info.type = CLIENT;
		return ;
	}
	else if (ac == 2)
	{
		s->info.type = STANDALONE;
		return ;
	}
	if (ft_strcmp(av[1], "-s") && ft_strcmp(av[1], "-c"))
		error("Error unknown option\nUsage: ./RT [-[s|c]] [scene.xml]");
	else if (!(ft_strcmp(av[1], "-s") && ft_strcmp(av[1], "-c")))
		s->info.type = !ft_strcmp(av[1], "-s") ? SERVER : CLIENT;
	else
		error("Error unknown option\nUsage: ./RT [-[s|c]] [scene.xml]");
	return ;
}
