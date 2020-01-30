/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 11:19:48 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/13 11:20:27 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	print_vector(t_vec3 v, char *name)
{
	printf("%s\nx:[%.75f]\ny:[%.75f]\nz:[%.75f]\n\n", name, v.x, v.y, v.z);
}

void	print_void(t_scene *s)
{
	t_nhit *cur;

	cur = s->void_regions;
	if (!cur)
	{
		printf("No void region\n");
		return ;
	}
	while (cur)
	{
		printf("Forbidden zone : %f - %f\n", cur->dist_st, cur->dist_lt);
		cur = cur->next;
	}
}
