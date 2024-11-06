/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:33 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/06 20:34:53 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>

char	*new_line_in_leftover(char *left, char *line, int j)
{
	line = ft_substr(left, 0, j + 1);  // Extract up to the newline
	ft_memmove(left, left + j + 1, ft_strlen(left) - j);  // Shift remaining content
	return (line);
}

char	*check_leftover(char *left, char *line)
{
	int		j = 0;

	while (left[j] != '\0')
	{
		if (left[j] == '\n')
		{
			line = new_line_in_leftover(left, line, j);
			return (line);
		}
		j++;
	}
	line = ft_strjoin(line, left);
	left[0] = '\0';
	return (line);
}

char	*buffer(int fd, char *left, char *buf)
{
	int		bytes_read;
	char	*line = malloc(1);
	int		i;

	i = 0;
	if (line)
		line[0] = '\0';

	// Check for remaining content in left
	if (left[0] != '\0')
	{
		line = check_leftover(left, line);
		if (ft_strchr(line, '\n'))
			return (line);
	}

	// Read loop
		while ((bytes_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes_read] = '\0';
		i = 0;

		// Look for newline in buf
		while (buf[i] != '\0')
		{
			if (buf[i] == '\n')
			{
				line = ft_strjoin(line, ft_substr(buf, 0, i + 1));
				ft_memmove(left, buf + i + 1, ft_strlen(buf) - i);
				return (line);
			}
			i++;
		}

		// Append the full buffer to line if no newline was found
		line = ft_strjoin(line, buf);
	}

	// Handle final leftover data at EOF
	if (bytes_read == 0 && left[0] != '\0')
	{
		line = ft_strjoin(line, left);
		left[0] = '\0';
		return (line);
	}
	if (bytes_read == 0 && line[0] != '\0')
		return (line);

	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	left[BUFFER_SIZE * 2];
	char		*buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || !buf)
		return (NULL);

	line = buffer(fd, left, buf);
	free(buf);
	return (line);
}

#include <stdio.h>
int	main(void)
{
	int	fd = open("text.txt", O_RDONLY);
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("LINE PRINTED: %s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
