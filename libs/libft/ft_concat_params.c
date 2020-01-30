/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:00:09 by gbianco           #+#    #+#             */
/*   Updated: 2018/11/22 02:13:02 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_arg_len(char **str)
{
	int		total;
	int		i;
	int		j;

	total = 0;
	i = 1;
	while (str[i])
	{
		j = 0;
		while (*str[j] != '\0')
		{
			total++;
			j++;
		}
		i++;
	}
	return (total);
}

char		*ft_concat_params(int argc, char **argv)
{
	int		i;
	char	*str;
	int		j;
	int		pt;

	str = (char*)malloc((ft_arg_len(argv) + 1 + (argc - 2)) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	pt = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			str[pt] = argv[i][j];
			j++;
			pt++;
		}
		if (i != argc - 1)
			str[pt++] = '\n';
	}
	str[pt] = '\0';
	return (str);
}
