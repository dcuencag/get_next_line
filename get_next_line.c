/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:42:19 by dancuenc          #+#    #+#             */
/*   Updated: 2025/02/27 12:43:55 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_update_stash(int fd, char *storage)
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
		tmp = storage;
		storage = ft_strjoin(storage, buff);
		free(tmp);
	}
	free(buff);
	return (storage);
}

char	*extract_line(char *current_line)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!current_line)
		return (NULL);
	if (current_line && (!ft_strchr(current_line, '\n')))
		return (current_line);
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

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line_read;
	char		*tmp;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stash = read_and_update_stash(fd, stash);
	if (ft_strchr(stash, '\n') || !ft_strchr(stash, '\0'))
	{
		line_read = extract_line(stash);
		if (!ft_strchr(stash, '\n'))
		{
			line_read = stash;
			stash = NULL;
			return (line_read);
		}
		//sacar esta parte y quitar strchr para poder tener solo 5 funciones en utils
		tmp = stash;
		stash = ft_substr(stash, ft_strchr(stash, '\n') - stash + 1, ft_strlen(stash));
		free(tmp);
		return (line_read);
	}
	if (stash && stash[0] != '\0')
	{
		line_read = stash;
		stash = NULL;
		return (line_read);
	}
	return (NULL);
}
/* 
int	main(void)
{
	int fd = open("hp.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open file.\n");
		return 1;
	}
 	char *line;
//	int i = 0;
//	line = get_next_line(fd);
	while ((line = get_next_line(fd)) != NULL)
	{
 		line = get_next_line(fd);
		i++;
		printf("%s", line);
	}
 
	printf("%s", get_next_line(fd));
 	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}*/