/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grodrig2 <grodrig2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:52:48 by grodrig2          #+#    #+#             */
/*   Updated: 2025/08/20 16:06:18 by grodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>  // para read()
#include <string.h>  // só se quiser usar funções padrão, mas na 42 geralmente fazem tudo manualmente

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

// Protótipos das funções auxiliares que você vai criar:
size_t	ft_strlen(const char *s);
char *ft_strjoin(char *s1, char *s2);
char *ft_strdup(const char *s);
char *ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);

#endif