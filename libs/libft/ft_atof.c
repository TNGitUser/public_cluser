/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 21:51:49 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/15 21:51:51 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	check_sign(char *str, int i, double d, int s)
{
	char	*tmp;
	int		x;
	int		ex;

	x = i;
	while (ft_isdigit(str[i]))
		i++;
	tmp = ft_strsub(str, x, i - x);
	ex = 1;
	while (++x <= i)
		ex = ex * 10;
	d += s < 0 ? -((double)ft_atoi(tmp) / ex) : ((double)ft_atoi(tmp) / ex);
	if (tmp != NULL)
		free(tmp);
	tmp = NULL;
	return (d);
}

double			ft_atof(char *str)
{
	double	d;
	int		i;
	int		s;

	s = 1;
	i = 0;
	while (str[i] <= 32 && str[i] > 0 && str[i] != 27)
		i++;
	d = ft_atoi(str + i);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] && str[i] != '.')
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (d);
		i++;
	}
	if (!str[i])
		return (d);
	i++;
	return (check_sign(str, i, d, s));
}
