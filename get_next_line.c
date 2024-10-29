/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:33 by gbartusc          #+#    #+#             */
/*   Updated: 2024/10/29 17:23:27 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

char	*set_line(char *line_buffer)
{
	line_buffer = '\0';
}

char	*buffer(int	fd, char *left , char *buf)
{
	int	bytes_read;
	int	i;
	char	*line;
	unsigned int	start;

	start = 0;
	i = 0;
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while(buf[i])
	{
		if (buf[i] == '\n')
		{
			line = ft_substr(buf, start, i + 1);
			left = ft_substr(buf, start + i + 1, BUFFER_SIZE - i - 1);
		}
	i++;
	}
	if (buf[i] == '\0')
		line = ft_strdup(buf);
	if (left[i])
	{
		line = ft_strjoin(left, line);
	}
}

char	*get_next_line(int fd)
{
	static char *left;
	char	*buf;

	left = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
    buffer(fd, left, buf);

	free(buffer);
}

void	main()
{
	int	fd;

	fd = open("text.txt", O_RDONLY);
	get_next_line(fd);
}