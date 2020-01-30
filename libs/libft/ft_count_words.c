/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:51:31 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/22 05:02:26 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words(char *str, char c)
{
	int		count;

	count = 0;
	while (*str != '\0')
	{
		while (*str == c && *str != '\0')
			str++;
		if (*str != c && *str != '\0')
			count++;
		while (*str != c && *str != '\0')
			str++;
	}
	return (count);
}
