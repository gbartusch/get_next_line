/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:33 by gbartusc          #+#    #+#             */
/*   Updated: 2024/10/31 17:51:04 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*buffer(int fd, char *left, char *buf)
{
	int				i;
	char			*line;
	unsigned int	start;

	i = 0;
	start = 0;
	read(fd, buf, BUFFER_SIZE);
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			line = ft_substr(buf, start, i + 1);
			printf("line that contains new line: %s\n", line);
			left = ft_substr(buf, start + i + 1, BUFFER_SIZE - i - 1);
			printf("leftover line: %s\n", left);
		}
		i++;
	}
	if (buf[i] == '\0') //if no \n found
	{
		if (left != NULL)
			left = ft_strjoin(left, line);
		else
			left = ft_strdup(buf);
		read(fd, buf, BUFFER_SIZE);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*left;
	char		*buf;
	char		*line;

	left = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	line = buffer(fd, left, buf);
	free(buf);
	buf = NULL;
	return (line);
}

#include <stdio.h>
void	main(void)
{
	int	fd;

	fd = open("text.txt", O_RDONLY);
	get_next_line(fd);
}
