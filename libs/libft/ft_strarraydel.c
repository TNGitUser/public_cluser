/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraydel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:22:47 by gbianco           #+#    #+#             */
/*   Updated: 2019/11/18 16:42:43 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strarraydel(char **strs)
{
	int	i;

	i = 0;
	if (strs == NULL)
		return ;
	while (strs[i] != NULL)
	{
		ft_strdel(&strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}
