/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:33 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/05 17:37:17 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*new_line_in_leftover(char *left, char *temp2, int j)
{
	char	*line;
	int		start;

	start = 0;
	line = ft_substr(left, start, j + 1);
	printf("line from left: %s\n", line);
	ft_memmove(left, left + j + 1, ft_strlen(left) - j);
	printf("line in left: %s\n", left);
	// ft_strcat(left, temp2);
	return (line);
}

char	*check_leftover(char *left, char *temp2)
{
	char	*line;
	int		j;

	j = 0;
	while (left[j] != '\0') //if there's leftover content
	{
		if (left[j] == '\n') //find the new line
		{	line = new_line_in_leftover(left, temp2, j);
			printf("line to be printed: %s\n", line);
			return (line);
		}
	j++;
	}
	printf("temp2: %s\n", temp2);
	if (!temp2)
		return (left);
	line = ft_strjoin(left, temp2);
	printf("line after join: %s\n", line);
	free (temp2);
	return (line);
	// line = ft_strdup(left);
	// left[0] = '\0';
}

char	*buffer(int fd, char *left, char *buf)
{
	int				i;
	char			*line;
	char			*temp2;
	unsigned int	start;
	int				bytes_read;

	i = 0;
	start = 0;
	temp2 = 0;
	bytes_read = read(fd, buf, BUFFER_SIZE);
	printf("buf: %s\n", buf);
	if (bytes_read == 0)
	{	line = check_leftover(left, temp2);
		printf("line in left: %s\n", left);
		printf("line: %s\n", line);
		return (line);
	}
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			temp2 = ft_substr(buf, start, i + 1);
			printf("temp2: %s\n", temp2);
			printf("left: %s\n", left);
			line = check_leftover(left, temp2);
			ft_memmove(buf, buf + i + 1, ft_strlen(buf) - i);
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
void	main(void)
{
	int	fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("line printed: %s\n", line);
	line = get_next_line(fd);
	printf("line printed: %s\n", line);
	line = get_next_line(fd);
	printf("line printed: %s\n", line);
	line = get_next_line(fd);
	printf("line printed: %s\n", line);
}
