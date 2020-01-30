/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:24:40 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/02 22:17:45 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static void	split_camera_tags(t_scene *s, char *camera)
{
	char	*cam[5];

	if (!(cam[0] = ft_strinstr(camera, "<position>", "</position>")))
		error("'position' tag of camera is missing");
	s->cam.pos = assign_vector(cam[0]);
	if (!(cam[1] = ft_strinstr(camera, "<direction>", "</direction>")))
		error("'direction' tag of camera is missing");
	s->cam.dir = assign_vector(cam[1]);
	if (!(cam[2] = ft_strinstr(camera, "<fov>", "</fov>")))
		error("'fov' tag of camera is missing");
	s->cam.fov = assign_double(cam[2]);
	if ((cam[3] = ft_strinstr(camera, "<rotation>", "</rotation>")))
		s->cam.rot = assign_vector(cam[3]);
	if ((cam[4] = ft_strinstr(camera, "<glare>", "</glare>")))
		s->cam.glr.select = assign_onoff(cam[4]);
	ft_strarraydeln(cam, 5, 0);
	ft_strdel(&camera);
}

static void	split_window_tags(t_scene *s, char *window)
{
	char		*dimension;
	double		dim[2];
	char		*title;
	char		*ambient;

	if (!(title = ft_strinstr(window, "<title>", "</title>")))
		error("'title' tag of window is missing");
	s->mlx.title = assign_char(title);
	ft_strdel(&title);
	if (!(dimension = ft_strinstr(window, "<dimension>", "</dimension>")))
		error("'dimension' tag of window is missing");
	assign_bidouble(dimension, &dim[0], &dim[1]);
	s->mlx.wid = dim[0];
	s->mlx.hei = dim[1];
	if (!(ambient = ft_strinstr(window, "<ambient>", "</ambient>")))
		error("'ambient' tag of window is missing");
	s->pix.amb = assign_double(ambient);
	ft_strdel(&dimension);
	ft_strdel(&ambient);
	ft_strdel(&window);
}

void		split_all_tags(t_scene *s, char *all)
{
	char	*scene;
	char	*camera;
	char	*window;

	if (!(scene = ft_strinstr(all, "<scene>", "</scene>")))
		error("'scene' block is missing");
	if (!(camera = ft_strinstr(scene, "<camera>", "</camera>")))
		error("'camera' block is missing");
	if (!(window = ft_strinstr(scene, "<window>", "</window>")))
		error("'window' block is missing");
	ft_strdel(&all);
	deep_count_camera_windows(camera, window);
	split_camera_tags(s, camera);
	split_window_tags(s, window);
	prcss_effects_tags(s, scene);
	split_allocated_tags(s, scene);
	ft_strdel(&scene);
}
