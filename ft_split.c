/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:32:25 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/14 13:32:35 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static char	**free_function(char **d, int i)
{
	while (i > 0)
	{
		i--;
		free(d[i]);
	}
	free(d);
	return (0);
}

static char	*putwords(const char *s, int i, char *word, int word_len)
{
	int	j;

	j = 0;
	while (word_len > 0)
	{
		word[j] = s[i - word_len];
		j++;
		word_len--;
	}
	word[j] = '\0';
	return (word);
}

static char	**malloc_words(const char *s, char c, char **d, int num_words)
{
	int	i;
	int	words;
	int	word_len;

	i = 0;
	words = 0;
	word_len = 0;
	while (words < num_words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			word_len++;
		}
		d[words] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!d[words])
			return (free_function(d, words));
		putwords(s, i, d[words], word_len);
		word_len = 0;
		words++;
	}
	d[words] = 0;
	return (d);
}

char	**ft_split(char const *s, char c)
{
	char			**d;
	unsigned int	num_words;

	num_words = count_words(s, c);
	d = (char **) malloc(sizeof(char *) * (num_words + 1));
	if (!d)
		return (NULL);
	d = malloc_words(s, c, d, num_words);
	return (d);
}
