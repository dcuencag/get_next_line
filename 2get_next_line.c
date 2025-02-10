/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:47:55 by dancuenc          #+#    #+#             */
/*   Updated: 2025/02/07 17:05:52 by dancuenc         ###   ########.fr       */
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

//To find '\n' || '\0'
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

char	*ft_strnjoin(char const *s1, char const *s2, int n)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*newstr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = malloc(s1_len + s2_len + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && n)
	{
		newstr[i] = s1[i];
		i++;
		n--;
	}
	while (s2[i - s1_len] != '\0'&& n)
	{
		newstr[i] = s2[i - s1_len];
		i++;
		n--;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*get_next_line(int fd)
{
	char	*read_line;
	char	*new_line;
	int		i;
	static int c = 0;
	static int n = 1;
	
	printf("HERE\n");
	printf("%d\n", n);
	n++;
// Create space to store content of txt
	read_line = malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!read_line)
		return(NULL);
		
//Create space to store content passing through read_line to concatenate
	new_line = malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!new_line)
		return(NULL);

//Read file till BUFFER_SIZE
	while (read(fd, read_line, BUFFER_SIZE))
	{
		i = 0;
		while (read_line[c] != '\n' && read_line[c] != '\0')
		{
			c++;
		}
	
//Write the line read and write it on new_line
		new_line = (char *)ft_strnjoin(&new_line[c], read_line, c);
		printf("here6\n");
	}
	printf("New line = %s\n", new_line);
	printf("here7\n");
	return (new_line);
}

int	main(void)
{
	char *str;
	int i = 0;
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
	str = get_next_line(fd);
	while (str[i] != '\0')
		str = get_next_line(fd);
	printf("gnl = %s\n", str);
/* 
	read(fd, storage, BUFFER_SIZE);
	printf("%s\n\n", storage);
	return (0); */
}