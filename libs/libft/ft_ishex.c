/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ishex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 05:26:05 by gbianco           #+#    #+#             */
/*   Updated: 2019/11/18 16:42:07 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	correct_base(int c)
{
	if ((c >= 'a' && c <= 'f') || (c >= '0' && c <= '9')\
		|| (c >= 'A' && c <= 'F'))
		return (1);
	else
		return (0);
}

int			ft_ishex(char *str)
{
	int i;

	if (ft_strlen(str) > 8)
		return (0);
	if (str[0] && str[0] != '0')
		return (0);
	if (str[1] && str[1] != 'x')
		return (0);
	i = 2;
	if (str[i] == 0)
		return (0);
	while (str[i] != 0)
	{
		if (correct_base(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
