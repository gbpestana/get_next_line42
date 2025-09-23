#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s)
	{
		s++;
		length++;
	}
	return (length);
}

char	*ft_strdup(const char *s)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	while (s[i] != '\0')
		i++;
	ptr = (unsigned char *)malloc(i + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return ((char *)ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	c_char;

	i = 0;
	c_char = c;
	while (s[i] != '\0')
	{
		if (s[i] == c_char)
			return ((char *)&s[i]);
		i++;
	}
	if (c_char == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1i;
	size_t	s2i;
	char	*sc;

	s1i = 0;
	s2i = 0;
	if (!s1 || !s2)
		return (NULL);
	sc = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!sc)
		return (NULL);
	while (s1[s1i] != '\0')
	{
		sc[s1i] = s1[s1i];
		s1i++;
	}
	while (s2[s2i] != '\0')
	{
		sc[s1i + s2i] = s2[s2i];
		s2i++;
	}
	sc[s1i + s2i] = '\0';
	return (sc);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	subs_len;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		subs_len = 0;
	else if (len > s_len - start)
		subs_len = s_len - start;
	else
		subs_len = len;
	subs = malloc(subs_len + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (i < subs_len)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[subs_len] = '\0';
	return (subs);
}

static char	*ft_read_and_fill(int fd, char *tmp, char *remainder)
{
	int		bytes_read;
	char	*old_remainder;

	bytes_read = 1;
	if (!remainder)
		remainder = ft_strdup("");
	while (!ft_strchr(remainder, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(remainder);
			return (NULL);
		}
		tmp[bytes_read] = '\0';
		old_remainder = remainder;
		remainder = ft_strjoin(remainder, tmp);
		free(old_remainder);
	}
	return (remainder);
}

static char	*ft_extract_line(char *remainder)
{
	int		i;
	char	*line;

	i = 0;
	if (!remainder || !remainder[0])
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		line = ft_substr(remainder, 0, i + 1);
	else
		line = ft_substr(remainder, 0, i);
	return (line);
}

static char	*ft_update_stash(char *remainder)
{
	int		i;
	char	*new_remainder;

	i = 0;
	if (!remainder)
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	new_remainder = ft_substr(remainder, i + 1, ft_strlen(remainder) - i);
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*chunk;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	chunk = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!chunk)
		return (NULL);
	remainder = ft_read_and_fill(fd, chunk, remainder);
	free(chunk);
	if (!remainder)
		return (NULL);
	line = ft_extract_line(remainder);
	remainder = ft_update_stash(remainder);
	return (line);
}

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strdup(const char *s);
char		*get_next_line(int fd);
#endif
