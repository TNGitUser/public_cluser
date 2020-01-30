/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 01:45:02 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:19:24 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLES_H
# define TRIANGLES_H

typedef struct				s_itrn
{
	t_vec3					v0;
	t_vec3					v1;
	t_vec3					v2;
	t_vec3					e0;
	t_vec3					e1;
	t_vec3					h0;
	t_vec3					s0;
	t_vec3					q0;
	double					a;
	double					f;
	double					u;
	double					v;
}							t_itrn;

#endif
