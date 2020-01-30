/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:21:09 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/17 10:16:41 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	swap(t_clt *x1, t_clt *x2)
{
	t_clt tmp;

	tmp = *x1;
	*x1 = *x2;
	*x2 = tmp;
}

int		partition(t_clt arr[], int low, int high)
{
	double	pivot;
	int		i;
	int		j;

	pivot = arr[high].t;
	i = (low - 1);
	j = low - 1;
	while (++j <= high - 1)
	{
		if (arr[j].t < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/*
**   arr[] --> Array to be sorted,
**   low  --> Starting index,
**   high  --> Ending index
*/

void	quicksort(t_clt arr[], int low, int high)
{
	int pi;

	if (low < high)
	{
		pi = partition(arr, low, high);
		quicksort(arr, low, pi - 1);
		quicksort(arr, pi + 1, high);
	}
}

/*
**	Desc : this function will sort clt by dist in obj but won't move the object
**			in the array.
*/

void	sort_clt(t_scene *s)
{
	int		i;

	i = -1;
	while (++i < s->n_obj - 1)
		quicksort(s->hit.clt, i * GRADE, (i + 1) * GRADE);
}
