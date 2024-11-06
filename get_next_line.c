/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:33 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/06 13:27:33 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>

char	*new_line_in_leftover(char *left, char *line, int j)
{
	int		start;

	start = 0;
	line = ft_substr(left, start, j + 1);
	printf("line from left: %s\n", line);
	ft_memmove(left, left + j + 1, ft_strlen(left) - j);
	printf("line in left: %s\n", left);
	
	return (line);
}

char	*check_leftover(char *left, char *line)
{
	int		j;
	j = 0;
	while (left[j] != '\0') //if there's leftover content
	{
		if (left[j] == '\n') //find the new line
		{	line = new_line_in_leftover(left, line, j);
			printf("line to be printed: %s\n", line);
			return (line);
		}
	j++;
	}
	line = ft_strjoin(left, line);
	printf("line after join: %s\n", line);
	// ft_memmove(left, left + j + 1, ft_strlen(left) - j);
	// if (left[j] == '\0')
	left[0] = '\0';
	printf("left after update: %s\n", left);
	return (line);
}

char	*buffer(int fd, char *left, char *buf)
{
	int				i;
	char			*line;
	unsigned int	start;
	int				bytes_read;

	i = 0;
	start = 0;
	line = malloc(1);
	if (line)
		line[0] = '\0';
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read < 0)
		return (NULL);
	buf[bytes_read] = '\0';
	printf("buf: %s\n", buf);
	if (bytes_read == 0)
	{	
		line = check_leftover(left, line);
		ft_strcat(left, buf);
		printf("left: %s\n", left);
		return (line);
	}
	if (left[0] != '\0')
	{
		line = check_leftover(left, line);
		if (line && ft_strchr(line, '\n'))
		{
			ft_strcat(left, buf);
			printf("left: %s\n", left);
			return (line);
		}
		
	}
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			ft_strcat(line, ft_substr(buf, start, i + 1));
			printf("line after buf added: %s\n", line);
			ft_memmove(buf, buf + i + 1, ft_strlen(buf) - i);
			printf("buf after buf update: %s\n", buf);
			ft_strcat(left, buf);
			printf("line in left: %s\n", left);
			printf("line: %s\n", line);
			return (line);
		}
	i++;
	}
	//if no \n found
	ft_strcat(left, buf);
	printf("line in left: %s\n", left);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	left[BUFFER_SIZE * 2];
	char		*buf;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	line = buffer(fd, left, buf);
	while (line == 0)
		line = buffer(fd, left, buf);
	free(buf);
		buf = NULL;
	return (line);
}

#include <stdio.h>
int	main(void)
{
	int	fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("LINE PRINTED: %s\n", line);
	line = get_next_line(fd);
	printf("LINE PRINTED: %s\n", line);
	line = get_next_line(fd);
	printf("LINE PRINTED: %s\n", line);
	line = get_next_line(fd);
	printf("LINE PRINTED: %s\n", line);
}
