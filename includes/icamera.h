/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icamera.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 02:01:34 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/19 18:22:07 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICAMERA_H
# define ICAMERA_H

# define DEFAULT_AXES 0
# define EXISTENT_AXES 1

typedef struct	s_initcam
{
	t_vec3		u_axe;
	t_vec3		v_axe;
	t_vec3		w_axe;
	double		h_wid;
	double		h_hei;
}				t_initcam;

#endif
