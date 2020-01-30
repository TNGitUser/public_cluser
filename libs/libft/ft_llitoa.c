/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 01:55:01 by gbianco           #+#    #+#             */
/*   Updated: 2019/04/24 01:55:28 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_llitoa(long long int n)
{
	char		*string;
	long int	nb;
	int			buffer;

	nb = n;
	buffer = ft_int_buffer(nb);
	if (!(string = ft_strnew(buffer)))
		return (NULL);
	string[buffer] = '\0';
	if (nb == 0)
		string[0] = '0';
	while (nb)
	{
		if (nb < 0)
		{
			string[0] = '-';
			nb = nb * -1;
		}
		string[buffer - 1] = (nb % 10) + 48;
		nb = nb / 10;
		buffer--;
	}
	return (string);
}
