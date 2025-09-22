/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grodrig2 <grodrig2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:52:48 by grodrig2          #+#    #+#             */
/*   Updated: 2025/09/05 14:46:55 by grodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_remove_line(char *source);
char	*ft_read_line(char *source);
char	*ft_read_and_save(int fd, char *storage);
char	*get_next_line(int fd);

size_t	ft_strlen_2(const char *s, int n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);

#endif
