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

char	*ft_strnjoin(char const *s1, char const *s2, int n)
{
    size_t	s1_len;
    size_t	i;
    char	*newstr;

    if (!s1)
        s1 = "";
    s1_len = ft_strlen(s1);
    newstr = malloc(s1_len + n + 1);
    if (!newstr)
        return (NULL);
    i = 0;
    while (s1[i] != '\0')
    {
        newstr[i] = s1[i];
        i++;
    }
    while (s2[i - s1_len] != '\0' && n)
    {
        newstr[i] = s2[i - s1_len];
        i++;
        n--;
    }
    newstr[i] = '\0';
    return (newstr);
}

char	*read_and_join(int fd, char *read_line)
{
    char	buffer[BUFFER_SIZE + 1];
    int		bytes_read;

    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read <= 0)
        return (read_line);
    buffer[bytes_read] = '\0';
    char *temp = read_line;
    read_line = ft_strnjoin(read_line, buffer, bytes_read);
    free(temp);
    return (read_line);
}

char	*extract_line(char *read_line, int i)
{
    char	*new_line;

    new_line = ft_strnjoin(NULL, read_line, i + 1);
    free(read_line);
    return (new_line);
}

char	*get_next_line(int fd)
{
    char	*read_line;
    char	*new_line;
    int		i;

    read_line = NULL;
    new_line = NULL;
    while ((read_line = read_and_join(fd, read_line)) != NULL)
    {
        if (!read_line)
            return (NULL);
        i = 0;
        while (read_line[i] != '\n' && read_line[i] != '\0')
            i++;
        if (read_line[i] == '\n')
            return (extract_line(read_line, i));
        new_line = ft_strnjoin(new_line, read_line, i);
        free(read_line);
        read_line = NULL;
    }
    if (read_line && *read_line)
        new_line = ft_strnjoin(new_line, read_line, ft_strlen(read_line));
    free(read_line);
    return (new_line);
}

int	main(void)
{
    char *str;
	int i = 1;
    int fd = open("try.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
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