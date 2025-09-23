#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif /* BUFFER_SIZE */

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*read_to_buffer(int fd, char *buffer);
char	*extract_line(char **buffer);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*free_buffer(char **buffer, char **read_buf);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);

#endif /* GET_NEXT_LINE_H */

char	*read_to_buffer(int fd, char *buffer);
char	*extract_line(char **buffer);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_to_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(&buffer);
	if (!line)
		return (free_buffer(&buffer, NULL));
	return (line);
}

char	*read_to_buffer(int fd, char *buffer)
{
	char	*temp;
	char	*read_buf;
	ssize_t	bytes_read;

	bytes_read = 1;
	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	read_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_buffer(&buffer, &read_buf));
		read_buf[bytes_read] = '\0';
		temp = ft_strjoin(buffer, read_buf);
		free_buffer(&buffer, NULL);
		buffer = temp;
	}
	free_buffer(&read_buf, NULL);
	if ((buffer[0] == '\0' || !buffer) && bytes_read == 0)
		return (free_buffer(&buffer, NULL));
	return (buffer);
}

char	*ft_strdup(const char *s1)
{
	char	*buffer;
	size_t	len;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	buffer = (char *)malloc(len + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		buffer[i] = s1[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*free_buffer(char **buffer, char **read_buf)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (read_buf && *read_buf)
	{
		free(*read_buf);
		*read_buf = NULL;
	}
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			len;
	void			*buffer;
	unsigned char	*ptr;
	size_t			i;

	if (nmemb != 0 && size > ((size_t) - 1) / nmemb)
		return (NULL);
	len = nmemb * size;
	buffer = malloc(len);
	if (!buffer)
		return (NULL);
	ptr = (unsigned char *)buffer;
	i = 0;
	while (i < len)
	{
		ptr[i] = 0;
		i++;
	}
	return (buffer);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*buffer;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	buffer = (char *)malloc(len_s1 + len_s2 + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (*s1)
		buffer[i++] = *s1++;
	while (*s2)
		buffer[i++] = *s2++;
	buffer[len_s1 + len_s2] = '\0';
	return (buffer);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	i;
	char	*buffer;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if ((start + len) > slen)
		len = slen - start;
	buffer = (char *)malloc(len + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < len)
	{
		buffer[i] = s[start];
		i++;
		start++;
	}
	buffer[i] = '\0';
	return (buffer);
}
