/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:40:11 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/01 09:21:09 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "../execution/execution.h"

static void	quote_check(char c, char *quote)
{
	if (c == '\'' || c == '"')
	{
		if (*quote == c)
			*quote = 0;
		else if (*quote == 0)
			*quote = c;
	}
}

static int	count_words(const char *s, char sep)
{
	int		i;
	int		count;
	int		in_word;
	char	quote;

	i = 0;
	count = 0;
	in_word = 0;
	quote = 0;
	while (s[i] != '\0')
	{
		quote_check(s[i], &quote);
		if ((s[i] != sep || quote) && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		if (s[i] == sep && !quote)
			in_word = 0;
		i++;
	}
	return (count);
}

static void	free_all(char **arr, int size)
{
	while (size >= 0)
	{
		free(arr[size]);
		size--;
	}
	free(arr);
}

static int	fill_word_array(char **arr, char const *s, char c)
{
	int		i;
	int		len;
	int		start;
	char	delimiter;

	i = 0;
	start = 0;
	while (i < count_words(s, c))
	{
		delimiter = c;
		while (s[start] == c)
			start++;
		if (s[start] == '\'' || s[start] == '\"')
			delimiter = s[start++];
		len = 0;
		while (s[start + len] && s[start + len] != delimiter)
			len++;
		arr[i] = ft_substr(s, start, len);
		if (!arr[i])
			return (free_all(arr, i - 1), 0);
		start += len + 1;
		i++;
	}
	arr[i] = NULL;
	return (1);
}

char	**ft_split_quotes(char const *s, char c)
{
	char	**strings;

	strings = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	if (!fill_word_array(strings, s, c))
		return (NULL);
	return (strings);
}