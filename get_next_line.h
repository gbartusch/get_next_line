/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginabartusch <ginabartusch@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:30 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/18 12:03:42 by ginabartusc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

char	*get_next_line(int fd);
char	*get_from_file(int fd, char *line, char *leftover);
char	*allocate_line(const char *get_from, char *leftover);
void	clear(char *leftover);

char	*join_allocated_strings(char *allocated_str1, char *allocated_str2);
bool	is_newline_found(const char *check);
size_t	newline_position(const char *check);
char	*gnl_strcpy(char *dst, const char *src);
size_t	gnl_strlen(char *str);

#endif