/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:33 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/04 20:21:48 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*buffer(int fd, char *left, char *buf)
{
	int				i;
	int				j;
	char			*line;
	char			*temp1;
	char			*temp2;
	unsigned int	start;
	int				bytes_read;

	i = 0;
	j = 0;
	start = 0;
	temp1 = 0;
	temp2 = 0;
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read == 0)
	{
		while (left[j] != '\0') //if there's leftover content
		{
			if (left[j] == '\n') //find the new line
			{
				line = ft_substr(left, start, j + 1);
				ft_memmove(left, left + j + 1, ft_strlen(left) - j);
				return (line);
			}
		j++;
		}
		line = ft_strdup(left);
		left[0] = '\0';
		return (line);
	}
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			temp2 = ft_substr(buf, start, i + 1);
			while (left[j] != '\0') //if something is in the leftover
			{
				if (left[j] == '\n') //find the new line
				{
					line = ft_substr(left, start, j + 1);
					ft_memmove(left, left + j + 1, ft_strlen(left) - j);
					ft_strcat(left, temp2);
					free (temp2);
					return (line);
				}
			j++;
			}
		//if no new line in leftover
		line = ft_strjoin(left, temp2);
		ft_strncpy(left, buf + i + 1, BUFFER_SIZE - i + 1);
		free (temp2);
		return (line);
		}
	i++;
	}
	//if no \n found
	ft_strcat(left, buf);
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
}
