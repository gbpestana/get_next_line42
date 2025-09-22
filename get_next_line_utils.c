/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grodrig2 <grodrig2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:57:04 by grodrig2          #+#    #+#             */
/*   Updated: 2025/08/20 16:06:04 by grodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_2(const char *s, int n)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (n == 1)
	{
		while (s[i] && s[i] != '\n')
			i++;
	}
	else
	{
		while (s[i])
			i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	i = 0;
	j = 0;
	joined = malloc(ft_strlen_2(s1, 0) + ft_strlen_2(s2, 0) + 1);
	if (!joined)
		return (NULL);
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	return (free(s1), joined);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *source)
{
	int		len;
	char	*duplicate;

	if (!source)
		return (NULL);
	len = ft_strlen_2(source, 0);
	duplicate = malloc((sizeof(char) * len) + 1);
	if (!duplicate)
		return (NULL);
	len = 0;
	while (source[len])
	{
		duplicate[len] = source[len];
		len++;
	}
	duplicate[len] = '\0';
	return (duplicate);
}
