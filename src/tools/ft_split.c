/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:55:23 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/03 19:27:26 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex.h"

//counts num of words in the string; set new_word flag to 1 if new word appears
static int	ft_count_words(const char *str, char c)
{
	int	i;
	int	j;
	int	new_word;

	if (!str)
		return (0);
	i = 0;
	j = 0;
	new_word = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && new_word == 0)
		{
			j++;
			new_word = 1;
		}
		else if (str[i] == c)
			new_word = 0;
		i++;
	}
	return (j);
}

//copies and returns every word char by char from start to end
static char	*ft_copy_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) *(end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

/*
 * goes up to the s len, because the NULL pointer should be set in the end
 * set new_word flag to -1, so the new_word can start from index s[0] or greater
 * delimiter appears - start to copy a new word until the next delimiter
 * if s[i] is not a start character after delim --> i++
 */
static void	ft_split_string(char **split, const char *s, char c)
{
	size_t	i;
	size_t	j;
	int		new_word;

	i = 0;
	j = 0;
	new_word = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && new_word == -1)
			new_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && new_word >= 0)
		{
			split[j] = ft_copy_word(s, (new_word), i);
			new_word = -1;
			j++;
		}
		i++;
	}
	split[j] = NULL;
}

/*
 * Allocates memory with malloc() and returns an array of strings obtained by
 * splitting ’s’ using the character ’c’ as a delimiter. The array must end with
 * a NULL pointer.
 * Returns the array of new strings resulting from the split. NULL if the
 * allocation fails.
 */
char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!split)
		return (NULL);
	ft_split_string(split, s, c);
	return (split);
}
