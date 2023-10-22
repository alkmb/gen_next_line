/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:14:08 by akambou           #+#    #+#             */
/*   Updated: 2023/09/28 18:31:48 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_line(int fd, char *backup)
{
	char	*buffer;
	int		read_line;

	read_line = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (crazy_free(&backup));
	while (read_line > 0 && !ft_strchr(backup, '\n'))
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line < 0)
		{
			crazy_free(&backup);
			return (crazy_free(&buffer));
		}
		if (read_line == 0 && !backup)
			return (crazy_free(&buffer));
		buffer[read_line] = '\0';
		backup = ft_strjoin(backup, buffer);
	}
	crazy_free(&buffer);
	return (backup);
}

static char	*get_backup(char *backup)
{
	int		start;
	int		end;
	char	*temp;

	start = 0;
	end = 0;
	while (backup[start] && backup[start] != '\n')
		++start;
	if (!backup[start])
		return (crazy_free(&backup));
	temp = malloc(sizeof(char) * (ft_strlen(backup) - start + 1));
	if (!temp)
		return (crazy_free(&backup));
	++start;
	while (backup[start + end] != '\0')
	{
		temp[end] = backup[start + end];
		++end;
	}
	temp[end] = '\0';
	crazy_free(&backup);
	return (temp);
}

static char	*get_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	if (backup[0] == '\0')
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\0')
		line = malloc(sizeof(char) * (i + 1));
	else
		line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup[OPEN_MAX];

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024)
		crazy_free(&backup[fd]);
	if (!backup[fd] || (backup[fd] && !ft_strchr(backup[fd], '\n')))
		backup[fd] = read_line(fd, backup[fd]);
	if (!backup[fd])
		return (NULL);
	line = get_line(backup[fd]);
	if (!line)
		return (crazy_free(&backup[fd]));
	backup[fd] = get_backup(backup[fd]);
	return (line);
}
