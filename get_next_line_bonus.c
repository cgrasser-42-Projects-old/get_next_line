/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:30:32 by cgrasser          #+#    #+#             */
/*   Updated: 2024/11/16 15:55:16 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*

	DESCRIPTION :
	get_next_line reads a file line by line, returning one line at a time.
	It uses a static buffer for each file descriptor (fd) to store the content
	between calls, so the file can be read incrementally. Each time it’s called,
	it reads the next line from the file, handles the buffer,
	and prepares the remaining content for future calls.

	RETURN VALUE :
	If a line is successfully read: returns the next line (with or without
	the trailing \n).
	If an error occurs or if the end of the file is reached: returns NULL.

	NOTES :
	The function uses a static buffer array (buffer[1024]), which means that
	each file descriptor (fd) maintains its own separate buffer for reading.
	It handles both the reading of new data and the extraction of lines and
	remaining text from the buffer.

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
	int		bytes_read;

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
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_from_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = extract_line(buffer[fd]);
	buffer[fd] = extract_remaining_text(buffer[fd]);
	return (line);
}
