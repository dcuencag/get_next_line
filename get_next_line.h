/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancuenc <dancuenc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:48:44 by dancuenc          #+#    #+#             */
/*   Updated: 2025/03/01 16:24:33 by dancuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/**
 * Read a line from a file descriptor
 * @param fd The file descriptor to read from
 * @return A pointer to the line read, or NULL if an error occurred
 */
char	*get_next_line(int fd);

/**
 * Set a block of memory to zero
 * @param pointer The pointer to the block of memory
 * @param size The size of the memory block
 */
void	ft_bzero(void *pointer, int size);

/**
 * Allocate and zero-initialize a block of memory
 * @param count The number of elements to allocate
 * @param size The size of each element
 * @return A pointer to the allocated memory block
 */
void	*ft_calloc(size_t count, size_t size);

/**
 * Calculate the length of a string
 * @param str The string to calculate the length of
 * @return The length of the string
 */
size_t	ft_strlen(const char *s);

/**
 * Concatenate two strings
 * @param s1 The first string
 * @param s2 The second string
 * @return A pointer to the concatenated string
 */
char	*ft_strjoin(char *stash, char *buffer);

/**
 * Extract a substring from a string
 * @param s The string to extract from
 * @param start The starting index of the substring
 * @param len The length of the substring
 * @return A pointer to the extracted substring
 */
char	*ft_substr(char *s, unsigned int start, size_t len);

/**
 * Find the first occurrence of a character in a string
 * 
 * @param s The string to search
 * @param c The character to find
 * @return Ptr to the first occurrence of c in the s, or NULL if not found
 */
char	*ft_strchr(char *s, int c);

#endif