/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:52:09 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/21 22:23:00 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*ptr;

	if (!(ptr = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!(ptr->content = (void *)malloc(content_size)))
		return (NULL);
	if (content == NULL)
	{
		ptr->content = NULL;
		ptr->content_size = 0;
		ptr->next = NULL;
		return (ptr);
	}
	ptr->content = ft_memcpy(ptr->content, content, content_size);
	ptr->content_size = content_size;
	ptr->next = NULL;
	return (ptr);
}
