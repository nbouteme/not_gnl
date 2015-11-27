/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 13:26:12 by nbouteme          #+#    #+#             */
/*   Updated: 2015/11/26 19:05:07 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "get_next_line.h"

static t_file_ptr	*new_file(int fd)
{
	t_file_ptr *file;

	file = malloc(sizeof(t_file_ptr));
	file->fd = fd;
	file->first = 0;
	file->len = 0;
	file->buf = ft_strnew(BUFF_SIZE + 1);
	return (file);
}

static int			read_next_line(t_file_ptr *file, char **line)
{
	int		e;
	char	*tmpbuf;
	char	*tmpptr;

	tmpbuf = ft_strnew(BUFF_SIZE + 1);
	file->first += file->len;
	file->len = ft_strindexof(file->buf + file->first, '\n') + 1;
	if (!file->len)
	{
		while (file->len <= 0 && (e = read(file->fd, tmpbuf, BUFF_SIZE)) >= 1)
		{
			tmpptr = file->buf;
			file->buf = ft_strjoin(file->buf, tmpbuf);
			ft_strclr(tmpbuf);
			free(tmpptr);
			file->len = ft_strindexof(file->buf + file->first, '\n') + 1;
		}
		free(tmpbuf);
		if (e == 0 && file->len == 0)
			*line = ft_strsub(file->buf, file->first, ~0U);
		if (e < 1)
			return (e);
	}
	*line = ft_strsub(file->buf, file->first, file->len - 1);
	return (1);
}

int					get_next_line(int const fd, char **line)
{
	static t_list	*files = 0;
	t_list			*l;

	if (!line)
		return (-1);
	l = files;
	while (l && ((t_file_ptr*)l->content)->fd != fd)
		l = l->next;
	if (!l)
	{
		l = ft_lstnew(new_file(fd), sizeof(t_file_ptr));
		ft_lstadd(&files, l);
	}
	return (read_next_line(l->content, line));
}
