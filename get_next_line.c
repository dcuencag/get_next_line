/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnltry.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:42:42 by dancuenc          #+#    #+#             */
/*   Updated: 2025/02/17 14:44:32 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"

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
	new_line[i] = current_line[i];
	return (new_line);
}

char *read_and_update_stash(int fd, char *stash)
{
    char buff[BUFFER_SIZE + 1];
    char *temp;
    int bytes_read;
	
	if (!stash)
		stash = malloc((sizeof(char) * 1) + 1);
		if(!stash)
			return (NULL);
	temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
    while (!stash || !ft_strchr(stash, '\n') || !ft_strchr(stash, '\0'))
    {
        bytes_read = read(fd, buff, BUFFER_SIZE);
        if (bytes_read <= 0)
            return (stash);
        buff[bytes_read] = '\0';
        temp = stash;
        stash = ft_strjoin(temp, buff);
        free(temp);
    }
    return (stash);
}

char *get_next_line(int fd)
{
    static char *stash;
    char *line_read;
	
    stash = read_and_update_stash(fd, stash);
    if (!stash)
        return (NULL);
    line_read = extract_line(stash);
    stash = ft_strchr(stash, '\n') ? ft_strdup(ft_strchr(stash, '\n') + 1) : NULL;
    return (line_read);
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
		printf(" %s", line);
	}
	close(fd);
	return 0;
}