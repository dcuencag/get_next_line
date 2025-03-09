/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:44:42 by dancuenc          #+#    #+#             */
/*   Updated: 2025/02/17 13:02:52 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"

char *extract_line(char *storage)
{
	char *new_line;
	int	i;

	if (storage && !ft_strchr(storage, '\n'))
		return (storage);
	new_line = malloc(sizeof(char) * ft_strlen(storage));
	if(!new_line)
		return (NULL);
	i = 0;
	while(storage[i] != '\n' && storage[i] != '\0')
	{
		new_line[i] = storage[i];
		i++;
	}
	new_line[i] = storage[i];
	return (new_line);
}

char *reading(char *storage, int fd)
{
	char *temp;
	char buf[BUFFER_SIZE + 1];
	int bytes_read;
	
	temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (!storage || !ft_strchr(storage, '\n') || !ft_strchr(storage, '\0'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
//		printf("\nbytes read = %d\n", bytes_read);
		if (bytes_read <= 0)
		{
			temp = storage;
			storage = NULL;
//			printf("\n RETURN OF READING = %s\n", temp);
			return (temp);
		}
		if(!storage)
		{
			free(storage);
			storage = malloc(sizeof(char) * BUFFER_SIZE + 1);
		}
		temp = storage;
		storage = ft_strjoin(temp, buf);
	}
//	printf("\nStorage after reading = %s\n", storage);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char *line_read;
	char *aux;

	storage = reading(storage, fd);
	if(!ft_strchr(storage, '\n'))
	{
		printf("\nhere\n");
		aux = storage;
		printf("\nStorage last = %s\n", storage);
		printf("\nAux last = %s\n", aux);
		storage = NULL;
		printf("\naux after null = %s\n", aux);
		return(aux);
	}
	if(ft_strchr(storage, '\n') || ft_strchr(storage, '\0'))
	{
		line_read = extract_line(storage);
		storage = ft_strchr(storage, '\n') + 1;
		return(line_read);
	}
	return (NULL);
}

int main()
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
		printf("%s", line);
	}
	close(fd);
	return 0;
}