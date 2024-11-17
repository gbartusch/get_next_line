/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:28 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/17 18:10:01 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char*	gnl_strcpy(char *dst, const char* src)
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
