/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:42:19 by dancuenc          #+#    #+#             */
/*   Updated: 2025/03/04 13:36:51 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Read from a file descriptor until a newline character is found
 * @param fd The file descriptor to read from
 * @param storage The string to store the read data
 * @return A pointer to the stored data, or NULL if an error occurred
 */
char	*read_to_stash(int fd, char *storage)
{
	char	*buff;
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	if (!storage)
		storage = ft_calloc(sizeof(char), 1);
	if (!storage)
		return (NULL);
	buff = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!ft_strchr(buff, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buff), free(storage), NULL);
		buff[bytes_read] = '\0';
// Realmente necesito tmp?
		tmp = storage;
		storage = ft_strjoin(storage, buff);
		free(tmp);
	}
	free(buff);
	return (storage);
}

/**
 * Extract a line from a string
 * @param current_line The string to extract the line from
 * @return A pointer to the extracted line, or NULL if an error occurred
 */
char	*extract_line(char *current_line)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!current_line)
		return (NULL);
	if (current_line && (!ft_strchr(current_line, '\n')))
	{
		return (current_line);
	}
	new_line = ft_calloc(sizeof(char), ft_strlen(current_line) + 2);
	if (!new_line)
		return (NULL);
	while (current_line[i] != '\n' && current_line[i] != '\0')
	{
		new_line[i] = current_line[i];
		i++;
	}
	new_line[i] = current_line[i];
	new_line[i + 1] = '\0';
	return (new_line);
}

/**
 * Update the stash after a line has been extracted
 * @param stash The string to update
 * @return A pointer to the updated stash
 */
char	*update_stash(char **stash)
{
	char	*line_read;
	char	*tmp;
	
	line_read = extract_line(*stash);
	if (!ft_strchr(*stash, '\n'))
	{
		line_read = *stash;
		*stash = NULL;
		return (line_read);
	}
	tmp = ft_strchr(*stash, '\n') + 1;
	*stash = ft_substr(tmp, 0, ft_strlen(tmp));
	tmp = NULL;
	return (line_read);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	if (ft_strchr(stash, '\n') || stash[0] != '\0')
		return (update_stash(&stash));
	free (stash);
	stash = NULL;
	return (NULL);
}

int	main(void)
{
	int fd = open("hp.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open file.\n");
		return 1;
	}
 	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("{%s}", line);
		free(line);
	}
//	printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}
