/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:50:05 by jlepere           #+#    #+#             */
/*   Updated: 2016/01/21 17:50:56 by jlepere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void		add_buff(t_buff *buff, char *data)
{
	int		c;
	char	*tmp_buff;
	char	*new_buff;

	if (buff->count == buff->size)
	{
		c = -1;
		new_buff = ft_strnew(buff->size + BUFF_SIZE);
		while (++c < buff->count)
			new_buff[c] = buff->data[c];
		tmp_buff = buff->data;
		buff->data = new_buff;
		buff->size += BUFF_SIZE;
		free(tmp_buff);
	}
	c = -1;
	while (++c < BUFF_SIZE)
		buff->data[buff->count++] = data[c];
}

static t_buff	*create_buff(const int fd)
{
	char	*data;
	t_buff	*buff;

	buff = (t_buff*)malloc(sizeof(t_buff));
	buff->data = ft_strnew(BUFF_SIZE);
	buff->size = BUFF_SIZE;
	buff->count = 0;
	buff->index = 0;
	buff->next = NULL;
	buff->fd = fd;
	data = ft_strnew(BUFF_SIZE);
	while (read(fd, data, BUFF_SIZE) > 0)
	{
		add_buff(buff, data);
		data = ft_strnew(BUFF_SIZE);
	}
	return (buff);
}

static t_buff	*select_buff(t_buff *buff, const int fd)
{
	while (buff->next && buff->fd != fd)
		buff = buff->next;
	if (buff->fd != fd)
		return (buff->next = create_buff(fd));
	return (buff);
}

int				get_next_line(int const fd, char **line)
{
	int				start;
	char			*data;
	t_buff			*buff;
	static t_buff	*begin;

	if (!line)
		return (-1);
	if (!begin)
		begin = create_buff(fd);
	buff = select_buff(begin, fd);
	start = buff->index;
	data = ft_strnew(BUFF_SIZE);
	while (buff->data[buff->index])
	{
		if (buff->data[buff->index] == '\n')
		{
			*line = ft_strsub(buff->data, start, buff->index++ - start);
			return (1);
		}
		buff->index++;
	}
	*line = ft_strsub(buff->data, start, buff->index - start);
	free(begin);
	begin = NULL;
	return (read(fd, data, BUFF_SIZE));
}
