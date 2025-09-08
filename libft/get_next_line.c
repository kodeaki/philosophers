/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:36:36 by tpirinen          #+#    #+#             */
/*   Updated: 2025/06/10 21:15:33 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_until_newline(int fd, char *buffer);
static char	*extract_line(const char *buffer);

char	*get_next_line(int fd)
{
	static char	left_overs[BUFFER_SIZE + 1];
	char		*buffer;
	char		*line;
	const char	*newline;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	buffer = ft_strjoin(left_overs, "");
	if (!buffer)
		return (NULL);
	buffer = read_until_newline(fd, buffer);
	if (!buffer || !*buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = extract_line(buffer);
	newline = ft_strchr(buffer, '\n');
	if (newline)
		ft_strcpy(left_overs, newline + 1);
	else
		left_overs[0] = '\0';
	free(buffer);
	return (line);
}

static char	*read_until_newline(int fd, char *buffer)
{
	char	read_buf[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	bytes_read;

	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		read_buf[bytes_read] = '\0';
		temp = buffer;
		buffer = ft_strjoin(buffer, read_buf);
		free(temp);
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}

static char	*extract_line(const char *buffer)
{
	char	*line;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}
