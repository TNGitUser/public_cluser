/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:11:53 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/10 15:18:02 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define MAXDEEP 10

int					openorclosed(char	*next);
char				*get_closed(char *next);
void				check_xml_validity(char *st);
void				check_if_correctly_nested(char *st);
int					count_all_tags(char *st);
int					count_tag_size(char *str);
int					count_word(char	*str, char *chk);
void				deep_precount_obj(char *object);
void				deep_count_primitive(char *object);
void				deep_count_triangle(char *object);
void				deep_precount_lht(char *light);
void				deep_count_plight(char *light);
void				deep_count_dlight(char *light);
void				deep_count_slight(char *light);
void				deep_count_rlight(char *light);
void				deep_count_effects(char *effects);
void				deep_count_camera_windows(char *camera, char *window);
t_vec3				assign_vector(char *str);
int					assign_hex(char *str);
int					assign_chartype(char *str);
int					assign_int(char	*str);
int					assign_axe(char *str);
int					assign_aa(char *str);
int					assign_onoff(char *str);
int					assign_colortype(char *str);
void				assign_bidouble(char *str, double *d1, double *d2);
double				assign_double(char *str);
char				*assign_char(char *str);
void				hardcheck_second_level(int count, char **next);
void				equalize_deep(int count, char **next);
void				find_and_replace(char *str, char *find, char *replace);
void				far_unlimited(char *src, char *start, char *end, char c);

#endif
