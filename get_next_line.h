/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 13:27:47 by nbouteme          #+#    #+#             */
/*   Updated: 2015/11/26 19:03:14 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFF_SIZE
#  define BUFF_SIZE 1
# endif

int				get_next_line(int const fd, char **line);

typedef struct	s_file_ptr
{
	int		fd;
	int		first;
	int		len;
	char	*buf;
}				t_file_ptr;

#endif
