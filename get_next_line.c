/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:33 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/14 10:13:04 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	chr;

	chr = c;
	while (*s != '\0')
	{
		if (*s == chr)
			return ((char *)s);
		s++;
	}
	if (chr == '\0')
		return ((char *)s);
	return (NULL);
}

char	*extract_line(char *line)
{
	size_t	line_size;
	char	*leftover;

	line_size = 0;
	while (line[line_size] != '\n' && line[line_size])
		line_size++;
	if (line[line_size] == '\0' || line[line_size + 1] == '\0')
		return (NULL);
	leftover = ft_substr(line, line_size + 1, ft_strlen(line) - line_size);
	if (!leftover)
		return (NULL);
	line[line_size + 1] = '\0';
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
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		if (!leftover)
			leftover = ft_strdup("");
		temp = leftover;
		leftover = ft_strjoin(temp, buf);
		free(temp);
		if (!leftover)
			return (NULL);
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
	if (!line)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	leftover = extract_line(line);
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
