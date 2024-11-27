/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:17:59 by cgrasser          #+#    #+#             */
/*   Updated: 2024/11/27 11:14:49 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*to_return;
	size_t	bytes;

	bytes = nmemb * size;
	if (size != 0 && nmemb > (-1 / size))
		return (NULL);
	to_return = (void *)malloc(bytes);
	if (to_return == NULL)
		return (NULL);
	ft_bzero(to_return, bytes);
	return (to_return);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str != c && *str)
		str++;
	if (*str == c)
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_size;
	char	*result;
	int		i;
	int		j;

	i = 0;
	total_size = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (total_size + 1));
	if (!result || !s1 || !s2)
		return (NULL);
	while (s1[i] != 0)
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
		result[i++] = s2[j++];
	result[total_size] = 0;
	return (result);
}
