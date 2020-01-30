/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:56:45 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/28 11:00:28 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			nerror(char *msg)
{
	ft_putstr(msg);
	ft_putchar('\n');
	return (-1);
}

void		error(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
	exit(EXIT_FAILURE);
}
