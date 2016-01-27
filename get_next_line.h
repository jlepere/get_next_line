/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:46:29 by jlepere           #+#    #+#             */
/*   Updated: 2016/01/22 10:01:12 by jlepere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32

typedef struct		s_buff
{
	int				fd;
	char			*data;
	int				size;
	int				count;
	int				index;
	struct s_buff	*next;
}					t_buff;

int					get_next_line(int const fd, char **line);

#endif
