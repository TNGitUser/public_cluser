/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 23:19:45 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 17:11:11 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void		*rtrn;

	if (!(rtrn = malloc(size)))
		return (NULL);
	ft_bzero(rtrn, size);
	return (rtrn);
}
