/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:10:48 by tpirinen          #+#    #+#             */
/*   Updated: 2025/07/16 14:51:22 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_count_words(char const *s, char c);
static char		**word_alloc(char **arr, char const *s, char c, size_t i);
static char		**fill_array(char **arr, char const *s, char c);
static void		ft_free_all(char **arr, size_t str_count);

/*	Allocates memory (using malloc(3)) and returns an array of strings
	obtained by splitting ’s’ using the character ’c’ as a delimiter.
	The array ends with a NULL pointer.										*/
char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	arr = malloc((word_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[word_count] = NULL;
	if (!fill_array(arr, s, c))
	{
		ft_free_all(arr, word_count);
		return (NULL);
	}
	return (arr);
}

/*	Counts the number words that are delimited
	by the character 'c'.													*/
size_t	ft_count_words(char const *s, char c)
{
	size_t	word_count;
	size_t	i;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			word_count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (word_count);
}

/*	Fills the array with the words.							*/
static char	**fill_array(char **arr, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (!word_alloc(arr, s, c, i))
				return (NULL);
			j = 0;
			while (*s && *s != c)
				arr[i][j++] = *s++;
			arr[i][j] = '\0';
		}
		i++;
	}
	return (arr);
}

/*	Allocates memory for a word												*/
static char	**word_alloc(char **arr, char const *word, char c, size_t i)
{
	size_t	word_size;
	char	*end_of_word;

	end_of_word = ft_strchr(word, (int)c);
	if (end_of_word == NULL)
		word_size = ft_strlen(word);
	else
		word_size = end_of_word - word;
	arr[i] = malloc(word_size + 1);
	if (!arr[i])
		return (NULL);
	return (arr);
}

/*	Frees the memory allocated to the words. Used when any of the
	memory allocations fail.												*/
static void	ft_free_all(char **arr, size_t word_count)
{
	size_t	i;

	i = 0;
	while (arr[i] && i < word_count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
