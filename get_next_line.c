/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginabartusch <ginabartusch@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:34:37 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/18 11:51:41 by ginabartusc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	leftover[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (is_newline_found(leftover))
		return (allocate_line(leftover, leftover));
	if (*leftover)
	{
		line = allocate_line(leftover, leftover);
		if (!line)
			return (NULL);
	}
	line = get_from_file(fd, line, leftover);
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
		if (is_newline_found(line))
			return (line);
		read_status = read(fd, buffer, BUFFER_SIZE);
		if (read_status == -1)
			return (clear(leftover), free(line), NULL);
		buffer[read_status] = '\0';
	}
	return (line);
}

char	*allocate_line(const char *get_from, char *leftover)
{
	char			*line;
	size_t			i;

	i = 0;
	line = malloc(sizeof(char) * newline_position(get_from) + 2);
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
