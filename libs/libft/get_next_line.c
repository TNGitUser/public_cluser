/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:57:43 by gbianco           #+#    #+#             */
/*   Updated: 2019/03/05 16:15:33 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_fd	*fd_switcher(const int fd, t_fd **head)
{
	t_fd			*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (temp->fdl == fd)
			return (temp);
		temp = temp->next;
	}
	if (!(temp = (t_fd*)malloc(sizeof(t_fd))))
		return (NULL);
	temp->complete = ft_strnew(0);
	temp->temp = temp->complete;
	temp->fdl = fd;
	temp->next = *head;
	*head = temp;
	return (temp);
}

int		fd_reader(const int fd, t_fd **list)
{
	char			buff[BUFF_SIZE + 1];
	int				ck;
	int				i;

	ck = 1;
	while (ck > 0)
	{
		if ((ck = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		if (buff[0] == '\0' && ck != 0)
			return (-1);
		buff[ck] = '\0';
		(*list)->complete = ft_strjoin((*list)->complete, buff);
		ft_strdel(&((*list)->temp));
		(*list)->temp = (*list)->complete;
		i = 0;
		while (buff[i] != '\n' && buff[i] != '\0')
			i++;
		if (buff[i] == '\n')
			break ;
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static	t_fd	*head;
	t_fd			*list;
	int				i;

	if (((list = fd_switcher(fd, &head)) == NULL) || (fd_reader(list->fdl,
					&list) == -1))
		return (-1);
	if (*(list->complete) == '\0')
		return (0);
	i = 0;
	while ((list->complete)[i] != '\n' && (list->complete)[i] != '\0')
		i++;
	*line = ft_strsub(list->complete, 0, i);
	if ((list->complete)[i] != '\0')
		list->complete = list->complete + i + 1;
	else
		list->complete = list->complete + i;
	return (1);
}
