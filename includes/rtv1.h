/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:28:28 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/29 11:01:49 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <pthread.h>
# include <mlx.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "vec.h"
# include "matrix.h"
# include "multidata.h"
# include "parser.h"
# include "loader.h"
# include "cluster.h"

# include <stdio.h>

# define THREAD 16
# define GRADE 2
# define OBJ 6

# define BIAS 1e-10
# define ANULL 1e-20
# define BIA2 1e-7
# define EPSILON 1e-5
# define ID_OFFSET 1e6
# define CAM_CORRECTION 0

# define SERVER		0
# define CLIENT		1
# define STANDALONE	2

/*
** -------------------OBJECTS------------------------
*/
typedef	struct		s_trn
{
	t_vec3			v0;
	t_vec3			v1;
	t_vec3			v2;
	t_vec3			pos;
}					t_trn;

typedef	struct		s_prm
{
	t_vec3			pos;
	double			dim;
}					t_prm;

typedef	struct		s_obj
{
	int				typ;
	int				neg;
	int				id;
	int				clr;
	double			shi[2];
	double			mtx[4][4];
	double			trx[4][4];
	int				inv_nrm;
	t_vec3			dir;
	t_vec3			tra;
	t_vec3			rot;
	t_vec3			blur;
	t_prm			*pr;
	t_trn			*tr;
}					t_obj;
/*
**-----------------END-OBJECTS---------------------
*/

/*
**----------------------LIGHT----------------------
*/

# define L_POINT 1
# define L_DIR 2
# define L_SPOT 3
# define L_RECT 4

typedef	struct		s_plt
{
	t_vec3			pos;
}					t_plt;

typedef	struct		s_dlt
{
	t_vec3			dir;
}					t_dlt;

typedef	struct		s_slt
{
	t_vec3			pos;
	t_vec3			dir;
	double			ang;
}					t_slt;

typedef	struct		s_alt
{
	t_vec3			pos;
	t_vec3			v;
	t_vec3			u;
	int				q_v;
	int				q_u;
	int				inv;
	t_vec3			u_v;
	t_vec3			u_u;
	t_slt			one;
}					t_alt;

typedef	struct		s_lht
{
	int				clr;
	int				typ;
	double			pow;
	t_plt			*p;
	t_dlt			*d;
	t_slt			*s;
	t_alt			*a;
}					t_lht;
/*
**-------------------ENDLIGHT--------------------
*/

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	char			*pst;
	void			*pim;
	char			*sst;
	void			*sim;
	char			*title;
	int				hei;
	int				wid;
	int				b;
	int				s;
	int				e;
	int				button_alt;
	void			*loader_ptr;
	char			*loader_str;
}					t_mlx;

typedef struct		s_glare
{
	int				select;
	int				*shadow;
	t_obj			*fakeplane;
}					t_glare;

typedef struct		s_cam
{
	int				select;
	double			fov;
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			rot;
	t_vec3			u;
	t_vec3			v;
	t_vec3			w;
	t_vec3			bottleft;
	t_vec3			vi_x;
	t_vec3			vi_y;
	t_glare			glr;
}					t_cam;

typedef struct		s_efc
{
	int				select;
	int				aa;
	int				blu[2];
	double			gly[2];
	t_vec3			rotaxe;
	int				toon;
	int				clrm;
	double			maxtime;
}					t_efc;

typedef	struct		s_ray
{
	t_vec3			ori;
	t_vec3			dir;
	double			time;
	double			*maxtime;
}					t_ray;

typedef struct		s_nhit
{
	double			dist_st;
	double			dist_lt;
	t_obj			*obj;
	struct s_nhit	*next;
}					t_nhit;

typedef	struct		s_clt
{
	t_obj			*obj;
	double			t;
	int				neg;
}					t_clt;

typedef	struct		s_hit
{
	double			tt[GRADE + 1];
	int				n_clt;
	t_clt			*clt;
	double			t;
	t_obj			*obj;
	t_vec3			isc;
	t_ray			*ray;
	t_vec3			nrm;
}					t_hit;

typedef	struct		s_pix
{
	double			amb;
	int				clr;
}					t_pix;

typedef struct		s_scene
{
	int				strt;
	int				n_obj;
	int				n_lht;
	int				n_wht;
	int				n_prt;
	t_obj			*obj;
	t_lht			*lht;
	t_cam			cam;
	t_cam			rstcam;
	t_mlx			mlx;
	t_hit			hit;
	t_nhit			*void_regions;
	t_pix			pix;
	t_efc			efc;
	int				var_obj;
	int				var_light;
	t_vec3			grp_mod[2];
	int				done;
	int				id;
	t_node			info;
	int				min_y;
	int				max_y;
}					t_scene;

/*
**	Fonction pointer
*/
typedef int			(*t_render)(t_scene*, t_ray*, double, double);
typedef void		(*t_normal)(double[4][1], double[4][1]);
typedef double		(*t_shader)(t_scene*, t_vec3);

/*
**	Render
*/
void				*select_image_mode(void *s);
void				multithr_single_image(t_scene *s);
void				anaglyph_multi_image(t_scene *s);
int					single_ray(t_scene *s, t_ray *r, double x, double y);
int					distribuited_rays(t_scene *s, t_ray *r, double x, double y);
void				color_secondary_pix(t_scene *s, int x, int y);
int					nerror(char *msg);
void				error(char *str);
void				effects_error(int check);
void				after_parse_error(int check);
void				after_parse_error2(int check);
/*
**	Camera
*/
void				precalc_camera(t_scene *s);
t_vec3				orientate_axes(t_scene *s, double x, double y);
t_vec3				quaternion_rotation_x(t_scene *s, t_vec3 dir);
t_vec3				quaternion_rotation_y(t_scene *s, t_vec3 dir);
t_vec3				quaternion_rotation_z(t_scene *s, t_vec3 dir);
t_vec3				quaternion_rotation_vec(t_vec3 a, t_vec3 b, double angle);
/*
**	Light and shading
*/
int					light(t_scene *s, t_shader f);
double				point_light(t_scene *s, t_lht *l, t_shader f);
double				direction_light(t_scene *s, t_lht *l, t_shader f);
double				spot_light(t_scene *s, t_lht *l, t_shader f);
double				rectangle_light(t_scene*s, t_lht *l, t_shader f);
t_vec3				center_of_sample(t_int2 k, t_lht *l);
double				camera_light(t_scene *s, int color);
void				init_camlight_data(t_scene *s);
int					get_color(t_scene *s, double *en, int clr, double amb);
double				classic_shader(t_scene *s, t_vec3 il);
double				cartoon_shader(t_scene *s, t_vec3 il);
double				camera_shader(t_scene *s, t_vec3 il);
/*
**	Intersections and normals
*/
void				collect_object_isc(t_scene *s, t_ray *r);
void				collect_shadow_isc(t_scene *s, t_ray *r);
void				get_object_hit(t_scene *s);
void				get_shadow_hit(t_scene *s);
void				object_intersection(t_obj *o, t_ray *r, double *t);
void				shadow_intersection(t_obj *o, t_ray *r, double *t);
void				intersect_ray_plane(t_ray *r, t_obj *o, double *t);
void				intersect_ray_disk(t_ray *r, t_obj *o, double *t);
void				intersect_ray_sphere(t_ray *r, t_obj *o, double *t);
void				intersect_ray_cylinder(t_ray *r, t_obj *o, double *t);
void				intersect_ray_cone(t_ray *r, t_obj *o, double *t);
void				intersect_ray_triangle(t_ray *r, t_obj *o, double *t);
t_vec3				find_intersection_point(t_ray *r, double *t);
t_vec3				get_norm(t_hit *dat, t_ray *r);
t_vec3				normal_at(t_hit *hit, t_normal f);
void				normal_sphere(double m[4][1], double d[4][1]);
void				normal_cylinder(double m[4][1], double d[4][1]);
void				normal_cone(double m[4][1], double d[4][1]);
t_vec3				normal_triangle(t_hit *dat, t_ray *r);
void				get_void_region(t_scene *s);
int					is_voided(t_nhit *void_region, double dist);
void				free_void_region(t_scene *s);
void				sort_clt(t_scene *s);
/*
**	Matrix transformations + translations + rotations
*/
void				add_transform_to_obj(t_obj *o);
t_ray				transform_ray(t_ray *r, t_obj *o);
void				obj_translation(t_obj *obj);
void				obj_rotations(t_obj *obj, double rot[4][4]);
void				rotate_triangle(t_obj *obj, t_vec3 *center);
void				rotate_mesh(t_scene *s, int *i);
void				rotate_xyz(t_vec3 *org, t_vec3 *rot);
/*
**	Color effects
*/
int					color_nored(int clr);
int					color_nocyan(int clr);
int					color_sepia(int clr);
int					color_negative(int clr);
int					color_grayscale(int clr);
/*
**	Visual effects
*/
int					aa_x2(t_scene *s, t_ray *r, t_crd2 c, t_render f);
int					aa_x4(t_scene *s, t_ray *r, t_crd2 c, t_render f);
void				time_switch(t_ray *r, t_obj *obj);
int					timed_rays(t_scene *s, t_ray *r, double x, double y);
int					global_blur(t_scene *s, t_ray *r, double x, double y);
double				determinate_max_time(t_scene *s);
int					cartoon_effect(t_scene *s, t_ray *r, double x, double y);
int					antialiasing(t_scene *s, t_ray *r, double x, double y);
int					average_color(int *rgb, int n);
/*
**	Events
*/
int					finish(void);
int					key_press_loop(int k, t_scene *s);
int					key_release_loop(int k, t_scene *s);
int					mouse_loop(int k, int x, int y, t_scene *s);
void				clean_scene(t_scene *s);
void				saving_image_ppm(t_scene *s);
/*
**	Parser
*/
void				obj_realloc(t_scene *s, int old_size);
void				parse(t_scene *s, char *av, int *ac, char *data);
void				count_tags(t_scene *s, char *str);
void				mesh_cycle(t_scene *s, char *scene);
void				objects_cycle(t_scene *s, char *scene, int i);
void				group_cycle(t_scene *s, char *scene);
void				process_group(t_scene *s, char *group, int id
		, t_vec3 mod[2]);
void				white_cycle(t_scene *s);
void				lights_cycle(t_scene *s, char *scene, int i);
void				split_all_tags(t_scene *s, char *all);
void				split_allocated_tags(t_scene *s, char *scene);
void				split_primitive_tags(t_scene *s, char *obj, int i);
void				split_triangle_tags(t_scene *s, char *obj, int i);
void				split_point_light(t_scene *s, char *light, int i);
void				split_directional_light(t_scene *s, char *light, int i);
void				split_spot_light(t_scene *s, char *light, int i);
void				split_rectangle_light(t_scene *s, char *light, int i);
void				split_mesh_group(t_scene *s, char *grp, char *cm[], int *i);
void				prcss_effects_tags(t_scene *s, char *scene);
void				split_group_light_dispatcher(t_scene *s, t_lht *light
		, t_vec3 mod[1]);
/*
**	After parser
*/
void				after_parser(t_scene *s, char *file);
void				improve_data(t_scene *s);
/*
**	Loader
*/
void				start_program(t_scene *s, int per, int oldper, int add);
void				compute_gradient(float percent, int (*color1)[3]
		, int (*color2)[3], int (*out)[3]);
void				printf_completion(int percentage);
void				update_visual(t_scene *s, int percentage);

/*
**	CLUSTER
*/
void				check_options(char **av, int ac, t_scene *s);
void				cluster(t_scene *s, char *file);
void				cluster_client(t_scene *s);
/*
**	DEBUG / TODO : to delete
*/
void				print_vector(t_vec3 v, char *name);
void				print_void(t_scene *s);
#endif
