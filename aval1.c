#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	cc;

	if (!s)
		return (NULL);
	cc = (unsigned char)c;
	while (*s && *s != cc)
		s++;
	if (*s == cc)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	j;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < s1_len)
		result[j++] = s1[i++];
	i = 0;
	while (i < s2_len)
		result[j++] = s2[i++];
	result [j] = '\0';
	return (result);
}

#include "get_next_line.h"

char	*ft_update_stock(char *stock)
{
	int		i;
	int		j;
	char	*new_stock;

	i = 0;
	while (stock[i] && stock [i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	new_stock = malloc(sizeof(char) * ft_strlen(stock) - i);
	if (!new_stock)
	{
		free(new_stock);
		return (NULL);
	}
	i++;
	j = 0;
	while (stock[i])
		new_stock[j++] = stock[i++];
	new_stock[j] = '\0';
	free(stock);
	return (new_stock);
}

char	*ft_extract_line(char *stock)
{
	int		i;
	char	*line;

	if (!stock || !*stock)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	line = malloc(i + (stock[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stock[i] && stock [i] != '\n')
	{
		line[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
		line [i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_read_and_stock(int fd, char *stock)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(stock), NULL);
	bytes_read = 1;
	while (!ft_strchr(stock, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stock), free(buffer), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(stock, buffer);
		free(stock);
		stock = temp;
	}
	free(buffer);
	if (bytes_read < 0 || (bytes_read == 0 && !stock))
		return (NULL);
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock = ft_read_and_stock(fd, stock);
	if (!stock || stock[0] == '\0')
	{
		free(stock);
		stock = NULL;
		return (NULL);
	}
	line = ft_extract_line(stock);
	stock = ft_update_stock(stock);
	return (line);
}

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_update_stock(char *stock);
char	*ft_extract_line(char *stock);
char	*ft_read_and_stock(int fd, char *stock);
char	*get_next_line(int fd);

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
#endif
