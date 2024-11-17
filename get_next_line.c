/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:34:37 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/17 20:02:08 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	leftover[BUFFER_SIZE + 1];
	char		*line;

	if (is_newline_found(leftover))
		return (allocate_line(leftover, leftover));
	line = get_line_from_file(fd, leftover);
	return (line);
}

char	*join_allocated_strings(char *allocated_str1, char *allocated_str2)
{
	char	*line;
	size_t	len;

	if (!allocated_str1 || !allocated_str2)
		return (free(allocated_str1), free(allocated_str2), NULL);
	len = gnl_strlen(allocated_str1);
	len += gnl_strlen(allocated_str2);
	line = malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	gnl_strcpy(line, allocated_str1);
	gnl_strcpy(line + gnl_strlen(line), allocated_str2);
	free(allocated_str1);
	free(allocated_str2);
	return (line);
}

char	*get_line_from_file(int fd, char *leftover)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
	int		read_status;

	line = NULL;
	read_status = read(fd, buffer, BUFFER_SIZE);
	if (read_status == -1)
		return (NULL);
	if (*leftover)
	{
		line = allocate_line(leftover, leftover);
		if (read_status == 0 || !line)
			return (line);
	}
	if (read_status == 0)
		return (NULL);
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
	}
	return (line);
}

char	*allocate_line(const char *get_from, char *leftover)
{
	char			*line;
	size_t			i;

	i = 0;
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

// #include "get_next_line.h"
// #include <stdio.h>

// int	main(void)
// {
// 	int	fd = open("text.txt", O_RDONLY);
// 	char	*line;

// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("LINE PRINTED: %s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }