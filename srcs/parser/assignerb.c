/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignerb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:11:51 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/22 19:03:30 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	assign_hex(char *str)
{
	int	hex;

	if (str[0] == '0' && (!(str[1])))
		return (0);
	if (ft_ishex(str) == 0)
		error("Plese check the format of hex values [0x000000]");
	hex = ft_atoi_base(str + 2, 16);
	return (hex);
}

int	assign_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '-')
			error("Please check the format of entire numbers");
		i++;
	}
	i = ft_atoi(str);
	return (i);
}

int	assign_chartype(char *str)
{
	char	*type[OBJ];
	int		i;

	type[0] = "plane";
	type[1] = "sphere";
	type[2] = "cylinder";
	type[3] = "cone";
	type[4] = "disk";
	type[5] = "triangle";
	i = -1;
	while (++i < OBJ)
		if (ft_strcmp(type[i], str) == 0)
			return (i);
	error("The object type doesn't exist");
	return (0);
}

int	assign_colortype(char *str)
{
	char	*type[OBJ];
	int		i;

	type[0] = "classic";
	type[1] = "sepia";
	type[2] = "grayscale";
	type[3] = "negative";
	i = -1;
	while (++i < OBJ)
		if (ft_strcmp(type[i], str) == 0)
			return (i);
	error("The color mode doesn't exist");
	return (0);
}
