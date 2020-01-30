/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:46:15 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/28 11:46:27 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	DANGER / WARNING : Only works if string is correctly formated
*/

void	string_to_color(char *str, t_node *node)
{
	if (!(str = ft_strchr(str, '[')))
		return ;
	node->info.color[0] = ft_atoi(str + 1);
	while (*str && *str != ',')
		++str;
	node->info.color[1] = ft_atoi(str + 1);
	++str;
	while (*str && *str != ',')
		++str;
	if (!str)
		error("Error in color conversion, missing last component");
	node->info.color[2] = ft_atoi(str + 1);
	return ;
}

char	*color_to_string(int colors[3])
{
	char	*output;
	char	*rgb[3];
	char	*tmp;

	rgb[0] = ft_itoa(colors[0]);
	rgb[1] = ft_itoa(colors[1]);
	rgb[2] = ft_itoa(colors[2]);
	tmp = ft_strnjoin(rgb[0], ",", rgb[1]);
	ft_memdel((void **)&rgb[0]);
	ft_memdel((void **)&rgb[1]);
	output = ft_strnjoin(tmp, ",", rgb[2]);
	ft_memdel((void **)&rgb[2]);
	ft_memdel((void **)&tmp);
	tmp = ft_strnjoin("[", output, "]");
	ft_memdel((void **)&output);
	output = tmp;
	if (!output)
		error("Failed to convert color to string");
	return (output);
}
