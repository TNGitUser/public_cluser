/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:47:51 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/22 02:49:47 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstcount(t_list *lst)
{
	size_t	index;

	index = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		index++;
	}
	return (index);
}
