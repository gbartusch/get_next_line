/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:34:37 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/20 15:44:27 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	leftover[OPEN_MAX][BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	if (is_newline_found(leftover[fd]))
		return (allocate_line(leftover[fd], leftover[fd]));
	if (*leftover[fd])
	{
		line = allocate_line(leftover[fd], leftover[fd]);
		if (!line)
			return (NULL);
	}
	line = get_from_file(fd, line, leftover[fd]);
	return (line);
}

char	*get_from_file(int fd, char *line, char *leftover)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_status;

	read_status = read(fd, buffer, BUFFER_SIZE);
	if (read_status == -1)
		return (clear(leftover), free(line), NULL);
	while (read_status > 0)
	{
		buffer[read_status] = '\0';
		if (!line)
			line = allocate_line(buffer, leftover);
		else
			line = \
				join_allocated_strings(line, allocate_line(buffer, leftover));
		if (!line)
			return (NULL);
		if (is_newline_found(line))
			return (line);
		read_status = read(fd, buffer, BUFFER_SIZE);
		if (read_status == -1)
			return (clear(leftover), free(line), NULL);
	}
	return (line);
}

char	*allocate_line(const char *get_from, char *leftover)
{
	char			*line;
	size_t			i;

	i = 0;
	if (is_newline_found(get_from))
		line = malloc(sizeof(char) * newline_position(get_from) + 2);
	else
		line = malloc(sizeof(char) * newline_position(get_from) + 1);
	if (!line)
		return (NULL);
	while (get_from[i] && get_from[i] != '\n')
	{
		line[i] = get_from[i];
		i++;
	}
	if (get_from[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	gnl_strcpy(leftover, get_from + i);
	return (line);
}

void	clear(char *leftover)
{
	*leftover = '\0';
}
