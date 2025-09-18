/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_update.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grodrig2 <grodrig2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:52:21 by grodrig2          #+#    #+#             */
/*   Updated: 2025/09/18 18:15:07 by grodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(char *source)
{
	int		len;
	char	*line;

	len = ft_strlen(source);
	line = malloc(len + (source[len] == '\n') + 1 );
	if (!line)
		return (free(line), NULL);
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

char	*ft_read_and_save(int fd, char *storage)
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
			return (free(storage), free(buffer), NULL);
		if (bytes == 0)
			break;
		buffer[bytes] = '\0';
		temp = ft_strjoin(storage, buffer);
		free(storage);
		storage = temp;
	}
	free(buffer);
	if (bytes < 0 || (!storage && bytes == 0))
		return (NULL);
	return (storage);
}

char	*get_next_line( int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = ft_read_and_save(fd, storage);
	if (!storage || storage[0] == '\0')
		return (free(storage), NULL);
	line = ft_read_line(storage);
	storage = ft_remove_line(storage);
	return (line);
}
