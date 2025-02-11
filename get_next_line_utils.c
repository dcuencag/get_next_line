/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:41 by dancuenc          #+#    #+#             */
/*   Updated: 2025/02/10 19:29:39 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
    size_t i = 0;
    while (s[i])
        i++;
    return (i);
}

char	*ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    return (NULL);
}

char	*ft_strdup(const char *s)
{
    char	*ptr;
    size_t	i = 0;

    ptr = malloc(ft_strlen(s) + 1);
    if (!ptr)
        return (NULL);
    while (s[i])
    {
        ptr[i] = s[i];
        i++;
    }
    ptr[i] = '\0';
    return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
    size_t	len1 = ft_strlen(s1);
    size_t	len2 = ft_strlen(s2);
    char	*newstr;
    size_t	i = 0, j = 0;

    newstr = malloc(len1 + len2 + 1);
    if (!newstr)
        return (NULL);
    while (s1 && s1[i])
    {
        newstr[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        newstr[i + j] = s2[j];
        j++;
    }
    newstr[i + j] = '\0';
    free(s1);
    return (newstr);
}
