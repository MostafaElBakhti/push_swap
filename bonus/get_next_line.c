/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:35:38 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/24 01:38:33 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd, char *remainder)
{
	char	*buffer;
	int		readed_bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (! buffer)
		return (free(remainder), NULL);
	readed_bytes = 1;
	while (! ft_strchr(remainder, '\n') && readed_bytes > 0)
	{
		readed_bytes = read(fd, buffer, BUFFER_SIZE);
		if (readed_bytes < 0)
			return (free(buffer), free(remainder), NULL);
		buffer[readed_bytes] = '\0';
		remainder = ft_strjoin(remainder, buffer);
		if (!remainder)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (remainder);
}

char	*extract_line(char *remainder)
{
	char	*line;
	int		i;
	size_t	len;

	if (!remainder || ! *remainder)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	len = i;
	if (remainder[i] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_remainder(char *remainder)
{
	char	*new_remainder;
	int		i;
	int		j;

	if (!remainder)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (! remainder[i])
		return (free(remainder), NULL);
	i++;
	new_remainder = malloc(ft_strlen(remainder + i) + 1);
	if (!new_remainder)
		return (free(remainder), NULL);
	j = 0;
	while (remainder[i])
		new_remainder[j++] = remainder[i++];
	new_remainder[j] = '\0';
	free(remainder);
	if (new_remainder[0] == '\0')
		return (free(new_remainder), NULL);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = ft_read_line(fd, remainder);
	if (!remainder)
		return (NULL);
	line = extract_line(remainder);
	if (!line)
		return (free(remainder), remainder = NULL, NULL);
	remainder = update_remainder(remainder);
	return (line);
}
