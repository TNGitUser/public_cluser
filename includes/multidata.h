/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multidata.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 02:05:20 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/26 23:51:45 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIDATA_H
# define MULTIDATA_H

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_crd2
{
	double			x;
	double			y;
}					t_crd2;

typedef struct		s_crd3
{
	double			i;
	double			j;
	double			k;
}					t_crd3;

typedef struct		s_int2
{
	int				i;
	int				j;
}					t_int2;

typedef struct		s_int3
{
	int				i;
	int				j;
	int				k;
}					t_int3;

#endif
