/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 23:34:28 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 23:45:42 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*start;

	if (lst == NULL)
		return (NULL);
	tmp = (*f)(lst);
	start = tmp;
	while (lst->next != NULL)
	{
		tmp->next = (*f)(lst->next);
		lst = lst->next;
		tmp = tmp->next;
	}
	return (start);
}
