/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraydeln.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:57:16 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/18 02:50:37 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strarraydeln(char **strs, int n, int f)
{
	int i;

	if (strs == NULL || f > 1)
		return ;
	i = -1;
	while (++i < n)
	{
		if (strs[i])
			ft_strdel(&strs[i]);
	}
	if (f == 1)
		free(strs);
	strs = NULL;
}
