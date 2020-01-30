/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:46:21 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/13 11:21:57 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static void	str_vector_validity(char *str)
{
	int		comma;
	int		i;

	comma = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (ft_isnumber(str[i]) == 0 && str[i] != ',')
			error("Please check the format of [x, y, z] cordinates");
		if (str[i] == ',')
			comma++;
	}
	if (comma != 2)
		error("Please check the format of [x, y, z] cordinates");
}

t_vec3		assign_vector(char *str)
{
	t_vec3	vec;
	int		i;

	if (str == NULL)
		return (v3(0, 0, 0));
	str_vector_validity(str);
	i = 0;
	vec.x = ft_atof(str);
	while (str[i] && str[i] != ',')
		i++;
	vec.y = ft_atof(str + i + 1);
	i++;
	while (str[i] && str[i] != ',')
		i++;
	vec.z = ft_atof(str + i + 1);
	return (vec);
}

double		assign_double(char *str)
{
	double	db;
	int		i;

	i = -1;
	while (str[++i] != '\0')
		if (ft_isnumber(str[i]) == 0)
			error("Plese check the format of real numbers");
	db = ft_atof(str);
	return (db);
}

void		assign_bidouble(char *str, double *d1, double *d2)
{
	int		comma;
	int		i;

	i = -1;
	comma = 0;
	if (str == NULL)
		return ;
	while (str[++i] != '\0')
	{
		if (ft_isnumber(str[i]) == 0 && str[i] != ',' && str[i] != ' ')
			error("Please check the format of double numbers [0, 0]");
		if (str[i] == ',')
			comma++;
	}
	if (comma != 1)
		error("Please check the format of double numbers [0, 0]");
	*d1 = ft_atof(str);
	i = 0;
	while (str[i] && str[i] != ',')
		i++;
	*d2 = ft_atof(&str[i + 1]);
}

char		*assign_char(char *str)
{
	char	*ch;

	if (ft_strlen(str) > 50)
		error("Title is too long [Max 50 characters]");
	if (ft_strchr(str, '<') != NULL)
		error("Title contain forbidenn characters");
	ch = ft_strdup(str);
	return (ch);
}
