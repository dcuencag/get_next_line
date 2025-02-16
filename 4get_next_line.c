/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4get_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:42:42 by dancuenc          #+#    #+#             */
/*   Updated: 2025/02/16 20:30:22 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *extract_line(char *current_line)
{
	char *new_line;
	int	i;

	if (current_line && !ft_strchr(current_line, '\n'))
		return (current_line);
	new_line = malloc(sizeof(char) * ft_strlen(current_line));
	if(!new_line)
		return (NULL);
	i = 0;
	while(current_line[i] != '\n' && current_line[i] != '\0')
	{
		new_line[i] = current_line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char *stash;
	char *line_read;
	char *temp;
	char buff[BUFFER_SIZE + 1];
	int bytes_read;

	temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (!ft_strchr(stash, '\n') || !ft_strchr(stash, '\0') || !stash)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		buff[bytes_read] = '\0';
		if (bytes_read <= 0)
		{
			temp = stash;
			free(stash);
			return (temp);
		}
		if(!stash)
			stash = temp;
		temp = stash;
		stash = ft_strjoin(temp, buff);
	} 
	if(ft_strchr(stash, '\n') || ft_strchr(stash, '\0'))
	{
		line_read = extract_line(stash);
		stash = ft_strchr(stash, '\n');
		return(line_read);
	}
	return (NULL);
}

int main()
{
	int fd = open("try4.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open file.\n");
		return 1;
	}
	char *line;
	int i = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("gnl call[%d] = %s\n", i++, line);
	}	
	close(fd);
	return 0;
}