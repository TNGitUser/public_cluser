/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 01:53:57 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/22 01:48:29 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		count;
	int		start;
	int		end;
	char	z;
	int		i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		count++;
		i++;
	}
	end = count - 1;
	start = 0;
	while (start < end)
	{
		z = str[start];
		str[start] = str[end];
		str[end] = z;
		start++;
		end--;
	}
	return (str);
}
