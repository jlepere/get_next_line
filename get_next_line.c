/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:50:05 by jlepere           #+#    #+#             */
/*   Updated: 2016/02/18 18:07:49 by jlepere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static t_gnld	*create_gnld(const int fd)
{
	char	*data;
	t_gnld	*gnld;

	data = ft_strnew(BUFF_SIZE);
	gnld = (t_gnld*)malloc(sizeof(t_gnld));
	gnld->fd = fd;
	gnld->index = 0;
	gnld->buff = new_cbuff();
	gnld->next = NULL;
	while (read(fd, data, BUFF_SIZE) > 0)
	{
		add_cbuff(gnld->buff, data);
		data = ft_strnew(BUFF_SIZE);
	}
	return (gnld);
}

static t_gnld	*select_gnld(t_gnld *gnld, const int fd)
{
	while (gnld->next && gnld->fd != fd)
		gnld = gnld->next;
	if (gnld->fd != fd)
		return (gnld->next = create_gnld(fd));
	return (gnld);
}

int				get_next_line(int const fd, char **line)
{
	int				start;
	char			*data;
	t_gnld			*curr;
	static t_gnld	*begin;

	if (!line)
		return (-1);
	if (!begin)
		begin = create_gnld(fd);
	curr = select_gnld(begin, fd);
	start = curr->index;
	data = ft_strnew(BUFF_SIZE);
	while (curr->buff->data[curr->index])
	{
		if (curr->buff->data[curr->index] == '\n')
		{
			*line = ft_strsub(curr->buff->data, start, curr->index++ - start);
			return (1);
		}
		curr->index++;
	}
	*line = ft_strsub(curr->buff->data, start, curr->index - start);
	free(begin);
	begin = NULL;
	return (read(fd, data, BUFF_SIZE));
}
