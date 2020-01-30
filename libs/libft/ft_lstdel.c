/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 18:44:38 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 18:43:38 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *temp;

	temp = NULL;
	while (*alst != NULL)
	{
		temp = *alst;
		ft_lstdelone(alst, del);
		*alst = (temp)->next;
	}
}
