/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:30 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/18 20:13:03 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

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