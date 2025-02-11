/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:13:57 by dancuenc          #+#    #+#             */
/*   Updated: 2025/02/10 19:29:29 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **stash)
{
    char	*line;
    char	*new_stash;
    int		i = 0;

    if (!*stash || !**stash)
        return (NULL);
    while ((*stash)[i] && (*stash)[i] != '\n')
        i++;
    line = malloc(i + 2);
    if (!line)
        return (NULL);
    line[i + 1] = '\0';
    while (i >= 0)
    {
        line[i] = (*stash)[i];
        i--;
    }
    if ((*stash)[i + 1] == '\0')
        new_stash = NULL;
    else
        new_stash = ft_strdup(*stash + i + 2);
    free(*stash);
    *stash = new_stash;
    return (line);
}

char	*get_next_line(int fd)
{
    static char	*stash;
    char		buffer[BUFFER_SIZE + 1];
    char		*temp;
    int			bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (!ft_strchr(stash, '\n') && (bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        temp = stash;
        stash = ft_strjoin(stash, buffer);
        if (!stash)
            return (free(temp), NULL);
        free(temp);
    }
    if (stash && *stash)
        return (extract_line(&stash));
    free(stash);
    stash = NULL;
    return (NULL);
}

int	main(void)
{
    char	*str;
    int		i = 1;
    int		fd = open("try.txt", O_RDONLY);

    if (fd == -1)
    {
        printf("Error opening file\n");
        return (1);
    }
    while ((str = get_next_line(fd)) != NULL)
    {
        printf("line[%d] = %s\n", i, str);
        free(str);
        i++;
    }
    close(fd);
    return (0);
}