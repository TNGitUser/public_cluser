/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:39:04 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/28 12:39:10 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	*extract_string(char **src, char start, char end)
{
	char	*cptr;
	char	*output;
	int		ex[2];
	int		i;

	ex[0] = -1;
	ex[1] = -1;
	i = 0;
	cptr = *src;
	while (cptr[i] && (ex[0] == -1 || ex[1] == -1))
	{
		if (i > 0 && cptr[i - 1] != '\\' && cptr[i] == start && ex[0] == -1)
			ex[0] = i + 1;
		else if (i == 0 && cptr[i] == start && ex[0] == -1)
			ex[0] = i + 1;
		else if (i > 0 && cptr[i - 1] != '\\' && cptr[i] == end && ex[0] != -1)
			ex[1] = i - 1;
		else if (i == 0 && cptr[i] == end && ex[0] != -1)
			ex[1] = i - 1;
		++i;
	}
	output = ft_strsub(*src, ex[0], ex[1]);
	*src += ex[1] + 2;
	return (output);
}

char	*strdelim(char **src, char c)
{
	char	*output;
	size_t	l;

	l = 0;
	while ((*src)[l] && (*src)[l] != c)
		++l;
	if (!(output = malloc(sizeof(char) * (l + 1))))
		error("strdelim malloc error");
	output[l] = '\0';
	strncpy(output, *src, l);
	*src += l;
	return (output);
}

size_t	strocc(char *src, char c)
{
	size_t count;

	if (!src || c == '\0')
		return (0);
	count = 0;
	while (*src)
	{
		if (*src == c)
			++count;
		++src;
	}
	return (count);
}

char	*strnjoin(char *src, char *add, char *end)
{
	char	*output;
	int		i;

	if (!src || !add || !end || !(output = malloc(sizeof(char)
					* (strlen(src) + strlen(add) + strlen(end) + 1))))
		return (NULL);
	i = 0;
	while (*src)
	{
		output[i++] = *src;
		++src;
	}
	while (*add)
	{
		output[i++] = *add;
		++add;
	}
	while (*end)
	{
		output[i++] = *end;
		++end;
	}
	output[i] = '\0';
	return (output);
}

char	*strjoin(char *src, char *add)
{
	char	*output;
	int		i;

	if (!src || !add)
		return (NULL);
	if (!(output = malloc(sizeof(char) * (strlen(src) + strlen(add) + 1))))
		return (NULL);
	i = 0;
	while (*src)
	{
		output[i++] = *src;
		++src;
	}
	while (*add)
	{
		output[i++] = *add;
		++add;
	}
	output[i] = '\0';
	return (output);
}
