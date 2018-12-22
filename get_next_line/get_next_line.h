/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 23:20:28 by kbatz             #+#    #+#             */
/*   Updated: 2018/12/22 21:30:21 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 15
# define STEP_SIZE 1

# include "libft/libft.h"
# include <libc.h>

typedef struct		s_file
{
	char			*line;
	int				fd;
}					t_file;

int					get_next_line(const int fd, char **line);

#endif
