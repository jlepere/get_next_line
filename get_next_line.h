/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:46:29 by jlepere           #+#    #+#             */
/*   Updated: 2016/02/18 17:52:58 by jlepere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32

# include "libft.h"

typedef struct		s_gnld
{
	int				fd;
	int				index;
	struct s_cbuff	*buff;
	struct s_gnld	*next;
}					t_gnld;

int					get_next_line(int const fd, char **line);

#endif
