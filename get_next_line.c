/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:33 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/03 18:22:54 by gbartusc         ###   ########.fr       */
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

	i = 0;
	j = 0;
	start = 0;
	temp1 = 0;
	temp2 = 0;
	read(fd, buf, BUFFER_SIZE);
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			temp2 = ft_substr(buf, start, i + 1);
			while (left[j] != '\0')
			{
				if (left[j] == '\n')
				{
					temp1 = ft_substr(left, start, j + 1);
					line = ft_strjoin(temp1, temp2);
				}
				else if (left[i] == '\0')
					line = ft_strjoin(left, temp2); //if left has no \n
			j++;
			}
			if (left[j] == '\0')
			line = ft_strcpy(temp2);
			printf("line that contains new line: %s\n", line);
			left = ft_substr(buf, start + i + 1, BUFFER_SIZE - i - 1);
			printf("leftover line: %s\n", left);
		}
		else if (buf[i] == '\0') //if no \n found
		{
			if (left != '\0')
				ft_strcat(left, buf);

			else
				left = ft_strcpy(buf);
		}
		i++;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	left[BUFFER_SIZE];
	char		*buf;
	char		*line;

	line = NULL;
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
