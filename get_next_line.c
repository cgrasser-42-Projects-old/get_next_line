/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:16:35 by cgrasser          #+#    #+#             */
/*   Updated: 2024/11/16 15:56:07 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*

	DESCRIPTION :
	get_next_line reads a file line by line. On each call, it returns the next
	line from the file, including the newline character (\n) if present,
	while keeping track of the remaining content for subsequent calls.

	RETURN VALUE :
	If a line is successfully read: returns the line (with or without
	the trailing \n).
	If the end of the file is reached or in case of an error: returns NULL.

*/

static char	*join_and_free(char *str1, char *str2)
{
	char	*temp;

	temp = ft_strjoin(str1, str2);
	free(str1);
	return (temp);
}

static char	*extract_remaining_text(char *str)
{
	char	*remaining;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	remaining = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	i++;
	j = 0;
	while (str[i])
		remaining[j++] = str[i++];
	free(str);
	return (remaining);
}

static char	*extract_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*read_from_file(int fd, char *content)
{
	char	*buffer;
	ssize_t	bytes_read;

	if (!content)
		content = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(content);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		content = join_and_free(content, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (content);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_from_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = extract_remaining_text(buffer);
	return (line);
}
