/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:13:57 by dancuenc          #+#    #+#             */
/*   Updated: 2025/02/12 12:57:56 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_found(char *new_line)
{
	int	i;

	i = 0;
	while (new_line[i] != '\0')
	{
		if (new_line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char *line_read;
	char buffer[BUFFER_SIZE + 1];
	char *temp;
	int bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line_read)
		line_read = ft_strdup("");

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (!ft_found(line_read) && bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = line_read;
		line_read = ft_strjoin(line_read, buffer);
		if (!line_read)
		{
			return (NULL);
			free(temp);
		}
		free(temp);
		temp = NULL;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == 0)
	{
		if (line_read && *line_read != '\0')
			return (line_read);
		free(line_read);
		line_read = NULL;
		return (NULL);
	}
	return (line_read);
}

int main()
{
	int fd = open("try.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open file.\n");
		return 1;
	}

	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
	}
	close(fd);
	return 0;
}