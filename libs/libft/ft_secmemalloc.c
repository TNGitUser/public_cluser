/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secmemalloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:02:00 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/17 15:15:58 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_secmemalloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
	{
		ft_putstr("Memory allocation problem\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(ptr, size);
	return (ptr);
}
