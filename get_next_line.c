/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:42:19 by dancuenc          #+#    #+#             */
/*   Updated: 2025/03/08 16:28:09 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *src)
{
	char	*dst;
	size_t	i;

	dst = malloc(sizeof(char) * (ft_strlen(src) + 1));
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	free(src);
	return (dst);
}

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
		return (free(storage), NULL);
	while (!ft_strchr(buff, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buff), free(storage), NULL);
		buff[bytes_read] = '\0';
		tmp = ft_strjoin(storage, buff);
		storage = ft_strcpy(tmp);
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

	if (!current_line)
		return (NULL);
	if (current_line && (!ft_strchr(current_line, '\n')))
	{
		return (current_line);
	}
	new_line = ft_calloc(sizeof(char), ft_strlen(current_line) + 2);
	if (!new_line)
		return (NULL);
	i = 0;
	while (current_line[i] != '\n' && current_line[i] != '\0')
	{
		new_line[i] = current_line[i];
		i++;
	}
	if (current_line[i] == '\n')
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
	char	*ptr;

	if (!stash)
		return (NULL);
	line_read = extract_line(*stash);
	if (!line_read)
		return (NULL);
	if (!ft_strchr(*stash, '\n'))
	{
		return (ft_strcpy(*stash));
	}
	tmp = ft_strchr(*stash, '\n') + 1;
	if (!tmp)
		return (NULL);
	ptr = ft_substr(tmp, 0, ft_strlen(tmp));
	tmp = NULL;
	free(*stash);
	*stash = ptr;
	return (line_read);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	if (ft_strchr(stash, '\n'))
		return (update_stash(&stash));
	line = ft_strcpy(stash);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	stash = NULL;
	return (line);
}
/* 
int	main(int ac, char **av)
{
	int fd = 0;
	char *line;

	if (ac != 2)
	{
		printf("Invalid number of arguments.\n");
		return (0);
	}
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file.\n");
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	if (line == NULL)
	printf("(null)");
	close(fd);
	return (0);
} */