/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:33 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/07 19:09:40 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	const char	*src1;
	char		*dst1;

	src1 = src;
	dst1 = dst;
	i = -1;
	if (src1 == dst1)
		return (dst);
	if (dst1 < src1)
	{
		while (++i < len)
			dst1[i] = src1[i];
	}
	else
	{
		while (len > 0)
		{
			dst1[len - 1] = src1[len - 1];
			len--;
		}
	}
	return (dst);
}

char	*new_line_in_leftover(char *left, size_t j)
{
	char	*line;

	line = ft_substr(left, 0, j + 1);// Extract up to the newline
	if (!line)
		return (NULL);
	ft_memmove(left, left + j + 1, ft_strlen(left) - j);// Shift remaining content
	return (line);
}

char	*check_leftover(char *left, char *line)
{
	size_t		j;
	char		*temp;

	j = 0;
	while (left[j] != '\0')
	{
		if (left[j] == '\n')
		{
			free (line);
			line = new_line_in_leftover(left, j);
			if (!line)
				return (NULL);
			return (line);
		}
		j++;
	}
	temp = line;
	line = ft_strjoin(line, left);
	if (!line)
	{
		free(temp);
		return (NULL);
	}
	free (temp);
	left[0] = '\0';
	return (line);
}

char	*buffer(int fd, char *left, char *buf)
{
	int		bytes_read;
	char	*line;
	int		i;
	char	*temp;
	char	*substr;

	line = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (left[0] != '\0') // Check for remaining content in left
	{
		line = check_leftover(left, line);
		if (!line)
			return (NULL);
		if (ft_strchr(line, '\n'))
			return (line);
	}
	while ((bytes_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes_read] = '\0';
		i = 0;
		while (buf[i] != '\0') // Look for newline in buf
		{
			if (buf[i] == '\n')
			{
				substr = ft_substr(buf, 0, i + 1);
				if (!substr)
				{
					free(line);
					return (NULL);
				}
				temp = line;
				line = ft_strjoin(line, substr);
				free (temp);
				free (substr);
				if (!line)
					return (NULL);
				ft_memmove(left, buf + i + 1, ft_strlen(buf) - i);
				return (line);
			}
			i++;
		}
		temp = line;
		line = ft_strjoin(line, buf); // Append the full buffer to line if no newline was found
		if (!line)
		{
			free(temp);
			return (NULL);
		}
		free (temp);
	}
	// if (bytes_read == 0 && left[0] != '\0') 	// Handle final leftover data at EOF
	// {
	// 	line = ft_strjoin(line, left);
	// 	left[0] = '\0';
	// 	return (line);
	// }
	if (bytes_read == 0 && line[0] != '\0')
		return (line);
	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	left[BUFFER_SIZE];
	char		*buf;
	char		*line;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || !buf)
	{
		free(buf);
		return (NULL);
	}
	line = buffer(fd, left, buf);
	free(buf);
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
