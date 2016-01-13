/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 13:26:12 by nbouteme          #+#    #+#             */
/*   Updated: 2016/01/13 18:36:00 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "get_next_line.h"

static t_file_ptr	*new_file(int fd)
{
	t_file_ptr *file;

	file = ft_memalloc(sizeof(t_file_ptr));
	file->fd = fd;
	file->buf = ft_strnew(BUFF_SIZE + 1);
	return (file);
}

static int			read_next_line(t_file_ptr *file, char **line)
{
	int		e;
	char	*tmpbuf;
	char	*tmpptr;

	tmpbuf = ft_strnew(BUFF_SIZE + 1);
	file->first += file->len + (file->buf[file->first + file->len] == '\n');
	file->len = ft_strindexof(file->buf + file->first, '\n');
	e = 1;
	while (file->len == -1 && (e = read(file->fd, tmpbuf, BUFF_SIZE)) > 0)
	{
		tmpptr = file->buf;
		file->buf = ft_strjoin(file->buf, tmpbuf);
		ft_strclr(tmpbuf);
		free(tmpptr);
		file->len = ft_strindexof(file->buf + file->first, '\n');
	}
	if (e == -1)
		return (e);
	if (e == 0)
		file->len = ft_strlen(file->buf) - file->first;
	free(tmpbuf);
	*line = ft_strsub(file->buf, file->first, file->len);
	return ((unsigned)file->first < ft_strlen(file->buf));
}

void				remove_file(t_list **head, t_list *l)
{
	t_file_ptr	*f;

	if (*head != l)
		while ((*head)->next != l)
			*head = (*head)->next;
	else
		*head = l->next;
	if (*head)
		(*head)->next = l->next;
	f = l->content;
	free(f->buf);
	free(f);
	free(l);
}

int					get_next_line(int const fd, char **line)
{
	static t_list	*files = 0;
	t_list			*l;
	int				e;

	if (!line)
		return (-1);
	l = files;
	while (l && ((t_file_ptr*)l->content)->fd != fd)
		l = l->next;
	if (!l)
	{
		l = ft_lstnewown(new_file(fd), sizeof(t_file_ptr));
		ft_lstadd(&files, l);
	}
	if ((e = read_next_line(l->content, line)) != 1)
		remove_file(&files, l);
	return (e);
}
