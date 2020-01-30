/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignersp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:55:11 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/30 15:46:52 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	assign_aa(char *str)
{
	char	*off;
	char	*two;
	char	*four;

	off = "off";
	two = "2x";
	four = "4x";
	if (ft_strcmp(str, off) == 0)
		return (0);
	else if (ft_strcmp(str, two) == 0)
		return (2);
	else if (ft_strcmp(str, four) == 0)
		return (4);
	else
		error("Antialiasing value is not correct [off, 2, 4]");
	return (0);
}

int	assign_onoff(char *str)
{
	char	*off;
	char	*on;

	off = "off";
	on = "on";
	if (ft_strcmp(str, off) == 0)
		return (0);
	else if (ft_strcmp(str, on) == 0)
		return (1);
	else
		error("Please check the format of on-off values [on, off]");
	return (0);
}

int	assign_axe(char *str)
{
	char	*x;
	char	*y;

	x = "x";
	y = "y";
	if (ft_strcmp(str, x) == 0)
		return (1);
	else if (ft_strcmp(str, y) == 0)
		return (2);
	else
		error("The movement axe is not correct [x, y]");
	return (0);
}
