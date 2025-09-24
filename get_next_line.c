/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grodrig2 <grodrig2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:52:21 by grodrig2          #+#    #+#             */
/*   Updated: 2025/09/23 13:06:13 by grodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_remove_line(char *source)
{
	char	*new_source;
	char	*line;
	size_t	len;

	line = ft_strchr(source, '\n');
	if (!line)
		return (free(source), NULL);
	len = ft_strlen_2(line + 1, 0);
	new_source = malloc(sizeof(char) * len + 1);
	if (!new_source)
		return (free(source), NULL);
	new_source[len] = '\0';
	len = 1;
	while (line[len])
	{
		new_source[len - 1] = line[len];
		len++;
	}
	free(source);
	return (new_source);
}

static char	*ft_read_line(char *source)
{
	int		len;
	char	*line;

	if (!source || !*source)
		return (NULL);
	len = ft_strlen_2(source, 1);
	line = malloc(len + (source[len] == '\n') + 1);
	if (!line)
		return (NULL);
	len = 0;
	while (source[len] && source[len] != '\n')
	{
		line[len] = source[len];
		len++;
	}
	if (source[len] == '\n')
		line[len++] = '\n';
	line[len] = '\0';
	return (line);
}

static char	*ft_read_and_save(int fd, char *storage)
{
	int		bytes;
	char	*buffer;
	char	*temp;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (free(storage), NULL);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(storage, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), free(storage), NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(storage, buffer);
		if (!temp)
			return (free(buffer), free(storage), NULL);
		storage = temp;
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = ft_read_and_save(fd, storage);
	if (!storage || storage[0] == '\0')
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	line = ft_read_line(storage);
	storage = ft_remove_line(storage);
	return (line);
}
