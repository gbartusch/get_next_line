/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginabartusch <ginabartusch@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:28 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/18 11:52:44 by ginabartusc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_allocated_strings(char *allocated_str1, char *allocated_str2)
{
	char	*line;
	size_t	len;

	if (!allocated_str1 || !allocated_str2)
		return (free(allocated_str1), free(allocated_str2), NULL);
	len = gnl_strlen(allocated_str1);
	len += gnl_strlen(allocated_str2);
	line = malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	gnl_strcpy(line, allocated_str1);
	gnl_strcpy(line + gnl_strlen(line), allocated_str2);
	free(allocated_str1);
	free(allocated_str2);
	return (line);
}

bool	is_newline_found(char *check)
{
	while (*check && *check != '\n')
		check++;
	return (*check);
}

size_t	newline_position(const char *check)
{
	size_t	position;

	position = 0;
	while (check[position] && check[position] != '\n')
	{
		position++;
	}
	return (position);
}

char	*gnl_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	gnl_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
