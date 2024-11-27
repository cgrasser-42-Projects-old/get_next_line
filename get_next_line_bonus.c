/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:30:32 by cgrasser          #+#    #+#             */
/*   Updated: 2024/11/27 11:40:55 by cgrasser         ###   ########.fr       */
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

static char	*join_and_free(char *buffer, char *tmp_buffer)
{
	char	*new_buffer;

	new_buffer = ft_strjoin(buffer, tmp_buffer);
	free(buffer);
	return (new_buffer);
}

static char	*extract_remaining_text(char *buffer)
{
	char	*remaining;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	remaining = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		remaining[j++] = buffer[i++];
	free(buffer);
	return (remaining);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*read_from_file(int fd, char *buffer)
{
	char	*tmp_buffer;
	int		bytes_read;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	tmp_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, tmp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(tmp_buffer);
			return (NULL);
		}
		tmp_buffer[bytes_read] = 0;
		buffer = join_and_free(buffer, tmp_buffer);
		if (ft_strchr(tmp_buffer, '\n'))
			break ;
	}
	free(tmp_buffer);
	return (buffer);
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
