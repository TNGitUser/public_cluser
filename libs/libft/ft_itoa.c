/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 00:37:04 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/22 02:38:14 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int n)
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
