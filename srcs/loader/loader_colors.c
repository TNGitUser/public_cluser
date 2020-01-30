/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:34:25 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/20 15:45:32 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	compute_gradient(float percent, int (*color1)[3], int (*color2)[3]
		, int (*out)[3])
{
	(*out)[0] = (*color1)[0] + percent * ((*color2)[0] - (*color1)[0]);
	(*out)[1] = (*color1)[1] + percent * ((*color2)[1] - (*color1)[1]);
	(*out)[2] = (*color1)[2] + percent * ((*color2)[2] - (*color1)[2]);
}

void	printf_completion(int percentage)
{
	char	*color;

	if (percentage < 20)
		color = "\033[38;2;255;0;0m";
	else if (percentage < 40)
		color = "\033[38;2;255;127;0m";
	else if (percentage < 60)
		color = "\033[38;2;127;255;127m";
	else if (percentage < 80)
		color = "\033[38;2;127;255;0m";
	else
		color = "\033[38;2;0;255;0m";
	printf("Current completion percentage : %s%i%%\033[0m\n", color
			, percentage);
}
