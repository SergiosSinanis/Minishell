/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:34:33 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 12:11:55 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_save_to_storage(int fd, char *buff, char *storage)
{
	char	*aide;
	int		bytes_read;

	while (1)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(storage);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buff[bytes_read] = '\0';
		if (!storage)
			storage = ft_strdup("");
		aide = storage;
		storage = ft_strjoin(aide, buff);
		free(aide);
		if (!storage)
			return (NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (storage);
}

static char	*extract_current_line_from_storage(char *storage)
{
	size_t	len;
	char	*new_line;

	len = 0;
	while (storage[len] && storage[len] != '\n')
		len++;
	if (storage[len] == '\n')
		new_line = ft_substr(storage, 0, len + 1);
	else
		new_line = ft_substr(storage, 0, len);
	return (new_line);
}

static char	*update_storage(char *storage)
{
	size_t	len;
	char	*new_storage;

	len = 0;
	while (storage[len] && storage[len] != '\n')
		len++;
	if (!storage[len] || !storage[len + 1])
	{
		free (storage);
		return (NULL);
	}
	new_storage = ft_substr(storage, len + 1, ft_strlen(storage) - len - 1);
	free (storage);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*current_line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	storage = read_and_save_to_storage(fd, buff, storage);
	free(buff);
	buff = NULL;
	if (!storage)
		return (NULL);
	current_line = extract_current_line_from_storage(storage);
	if (!current_line)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = update_storage(storage);
	return (current_line);
}
