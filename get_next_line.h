/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:44 by dancuenc          #+#    #+#             */
/*   Updated: 2025/02/17 17:09:02 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif


char	*get_next_line(int fd);

/**
 * Concatenate two strings
 * @param s1 The first string
 * @param s2 The second string
 * @return A pointer to the concatenated string
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * Find the first occurrence of a character in a string
 * 
 * Modified to extract the last position of the str
 * @param s The string to search
 * @param c The character to find
 * @return A pointer to the first occurrence of the character in the string, or NULL if not found
 */
char	*ft_strchr(const char *s, int c);

/**
 * Duplicate a string
 * @param s1 The string to duplicate
 * @return A pointer to the duplicated string
 */
char	*ft_strdup(const char *s);

/**
 * Calculate the length of a string
 * @param str The string to calculate the length of
 * @return The length of the string
 */
size_t	ft_strlen(const char *s);

/**
 * Extract a substring from a string
 * @param s The string to extract from
 * @param start The starting index of the substring
 * @param len The length of the substring
 * @return A pointer to the extracted substring
 */
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif