/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:42:42 by dancuenc          #+#    #+#             */
/*   Updated: 2025/02/20 14:33:32 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"

char *read_and_update_stash(int fd, char *storage)
{
    char *buff;
    int bytes_read;

	bytes_read = 1;
	if (!storage)
		storage = malloc((sizeof(char) + 1));
	if(!storage)
		return(NULL);
//	me elimina los leaks pero termina de leer en la primera linea
//	buff[0] = '\0';
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buff), free(storage), NULL);
		buff[bytes_read] = '\0';
		if (bytes_read != 0)
			storage = ft_strjoin(storage, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (storage);
}

char *extract_line(char *current_line)
{
	char *new_line;
	int	i;

	i = 0;
	if (!current_line)
		return(NULL);
	if (current_line && (!ft_strchr(current_line, '\n')))
		return (current_line);
	new_line = malloc(sizeof(char) * ft_strlen(current_line));
	if(!new_line)
		return (NULL);

	while(current_line[i] != '\n' && current_line[i] != '\0')
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
	static char *stash = NULL;
	char *line_read;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stash = read_and_update_stash(fd, stash);
	if(ft_strchr(stash, '\n') || !ft_strchr(stash, '\0'))
	{
		line_read = extract_line(stash);
		if (!ft_strchr(stash, '\n'))
		{
			line_read = stash;
			stash = NULL;
			return(line_read);
		}
		stash = ft_strchr(stash, '\n') + 1;
		return(line_read);
	}
	if (stash && stash[0] != '\0')
	{
		line_read = stash;
		stash = NULL;
		return (line_read);
	}
	return(NULL);
}
/*
int main()
{
	int fd = open("hp.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open file.\n");
		return 1;
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
	char *line;
	int i = 0;
	line = get_next_line(fd)
	while (i < 44)
	{
		line = get_next_line(fd);
		i++;
		printf("%s", line);
 		if(!ft_strchr(line, '\n'))
			break;
	}
		printf("\n[%d]\n", i);
	close(fd);
	return 0;
}*/
