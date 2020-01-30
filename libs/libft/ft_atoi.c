/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 21:52:05 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/15 21:52:08 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int			n;
	int			neg;
	const char	*st;

	st = str;
	n = 0;
	neg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	if (*str > '9' || *str < '0')
		return (0);
	while ((*str <= '9' && *str >= '0') && *str != '\0')
	{
		n = (n * 10) + ((*str) - 48);
		str++;
	}
	str = st;
	return (n * neg);
}
