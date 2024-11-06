/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbartusc <gbartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:30 by gbartusc          #+#    #+#             */
/*   Updated: 2024/11/06 11:58:00 by gbartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>

char	*get_next_line(int fd);
char	*buffer(int fd, char *left, char *buf);
char	*check_leftover(char *left, char *line);
char	*new_line_in_leftover(char *left, char *line, int j);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strcat(char *dest, char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcpy(char *dst, char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);


#endif