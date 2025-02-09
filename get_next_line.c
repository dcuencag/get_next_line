/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:47:55 by dancuenc          #+#    #+#             */
/*   Updated: 2025/02/06 19:46:14 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	c = (unsigned char)c;
	i = 0;
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	*read_line;
	char	*new_line;
	int		i;
	
// Create space to store content of txt
	read_line = malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!read_line)
		return(NULL);
//Create space to store content passing through read_line to concatenate
	new_line = malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!new_line)
		return(NULL);
//Read file till BUFFER_SIZE
	read(fd, read_line, BUFFER_SIZE);
	i = 0;
//Figure out if there's a \n in the str read
	if (!ft_strchr(read_line, '\n'))
	{
//Hold the part of the txt read to concatenate till \n and return later
		new_line = read_line;
		i = i + BUFFER_SIZE;
	}
	printf("Read line = %s\n\n", read_line);
//Write the line read and write it on new_line
	while (read_line[i] != '\0')
	{
		if (read_line[i] == '\n')
			return (new_line);
		new_line[i] = read_line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

int	main(void)
{
/* 	char *storage = malloc(sizeof(char *) * BUFFER_SIZE + 1);
	int counter;
 */
/* 	if (ac != 2)
		printf("Only 1 argument please"); */
	printf("BUFFER_SIZE = %d\n\n", BUFFER_SIZE);
	int fd = open("try.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error abriendo archivo");
		return (1);
	}
	printf("gnl= %s\n", get_next_line(fd));
/* 
	read(fd, storage, BUFFER_SIZE);
	printf("%s\n\n", storage);
	return (0); */
}