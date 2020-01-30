/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:54:23 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/30 12:44:00 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char	*read_file(int fd)
{
	char	str[128 +1];
	char	*tmp;
	char	*input;
	int		rb;

	if (!(input = malloc(sizeof(char) * 2)))
		error("Read_file malloc failed");
	input[0] = '\0';
	rb = 128;
	while (rb > 0)
	{
		if ((rb = read(fd, str, 128)) <= 0)
		{
			if (rb == 0)
				break ;
			else
				error("Read_file read error");
		}
		str[rb] = '\0';
		tmp = input;
		input = strjoin(input, str);
		free(tmp);
	}
	return (input);
}

char		*get_data_filename(char *file)
{
	char	*data;
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 3)
		error("Get_data_filename failed open");
	data = read_file(fd);
	if (close(fd))
		error("Get_data_filename close failed");
	return (data);
}
