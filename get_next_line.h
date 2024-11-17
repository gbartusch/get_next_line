/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:30 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/17 18:07:13 by gbartusc         ###   ########.fr       */
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
char	*join_allocated_strings(char *allocated_str1, char *allocated_str2);
size_t	gnl_strlen(char *str);
char	*get_line_from_file(int fd, char *leftover);
bool	is_newline_found(char *check);
size_t	newline_position(const char *check);
char	*allocate_no_newline(char *source);
char	*allocate_line(const char *get_from, char *leftover);
char*	gnl_strcpy(char *dst, const char* src);

#endif