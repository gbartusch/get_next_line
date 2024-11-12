/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginabartusch <ginabartusch@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:33 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/12 04:47:18 by ginabartusc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>

char	*extract(char *line)
{
	size_t	count;
	char	*leftover;

	count = 0;
	while (line[count] != '\n' && line[count])
		count++;
	if (line[count] == '\0' || line[count + 1] == '\0')
		return (NULL);
	leftover = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (!leftover)
		return(NULL);
	line[count + 1] = '\0';
	return (leftover);
}

char	*buffer(int fd, char *buf, char *leftover)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		if (!leftover)
			leftover = ft_strdup("");
		temp = leftover;
		leftover = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (leftover);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*leftover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = buffer(fd, buf, leftover);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	leftover = extract(line);
	return (line);
}

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
