/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_group_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:00:23 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/16 13:31:02 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "parser.h"
#include <string.h>

void		obj_realloc(t_scene *s, int old_size)
{
	int			i;
	t_obj		*obj_array;

	if (!(obj_array = ft_secmemalloc(sizeof(t_obj) * (s->n_obj + s->n_wht))))
		error("Object array realloc failed");
	i = -1;
	while (++i < (old_size))
		s->obj[i] = obj_array[i];
	ft_memdel((void **)&(s->obj));
	s->obj = obj_array;
}

static int	far_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 == *s2 && n - 1 > 0 && *s1 != '\0' && *s2 != '\0')
	{
		n--;
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static int	far_aux(char *str[3], char c, int *i, int *j)
{
	if (str[0][*i] && !far_strncmp((str[0] + *i), str[2], ft_strlen(str[2])))
	{
		while (str[0][*i] && (*j)-- > 0)
			str[0][(*i)++] = c;
		return (1);
	}
	return (0);
}

void		far_unlimited(char *src, char *start, char *end, char c)
{
	int	i;
	int	j[2];

	j[1] = 0;
	j[0] = ft_strlen(end);
	i = 0;
	while (src && src[i])
	{
		if (!far_strncmp(src + i, start, ft_strlen(start)))
		{
			while (src[i] && (far_strncmp((src + i), end, ft_strlen(end))
						|| j[1] != 0))
			{
				if (!far_strncmp((src + i), start, ft_strlen(start)))
					j[1]++;
				else if (!far_strncmp((src + i), end, ft_strlen(end)))
					if (--j[1] == 0)
						break ;
				src[i++] = c;
			}
			if (far_aux((char *[3]) { src, start, end }, c, &i, &(j[0])))
				return ;
		}
		i = src[i] ? i + 1 : i;
	}
}
