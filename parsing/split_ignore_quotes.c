/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ignore_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:16:59 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/30 17:12:01 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "parsing.h"

static int	count_words_ignore_quotes(char *str, char c)
{
	bool	inquote;
	bool	indquote;
	int		i;
	int		count;
	int		inword;

	i = 0;
	inword = false;
	count = 0;
	inquote = false;
	indquote = false;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		if (str[i] == c && (!inquote && !indquote))
			inword = false;
		else if (!inword)
		{
			inword = true;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*word_copy_ignorequotes(char **s, char c)
{
	char	*dest;
	int		counter;
	bool	inquote;
	bool	indquote;

	inquote = false;
	indquote = false;
	counter = 0;
	while ((**s == c) && (**s != '\0'))
		(*s)++;
	while ((((**s != c) || inquote || indquote) && (**s != '\0')))
	{
		counter++;
		if ((**s) == '\'' && !indquote)
			inquote = !inquote;
		else if ((**s) == '\"' && !inquote)
			indquote = !indquote;
		(*s)++;
	}
	dest = malloc(sizeof(char) * (counter + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, ((*s) - counter), counter + 1);
	return (dest);
}

char	**split_ignore_quotes(char *str, char c)
{
	int		i;
	char	**arr;
	int		wordnbr;

	i = 0;
	wordnbr = count_words_ignore_quotes(str, c);
	arr = malloc(sizeof(char *) * (wordnbr + 1));
	if (!arr)
		return (NULL);
	while (i < wordnbr)
	{
		arr[i] = word_copy_ignorequotes(&str, c);
		if (arr[i] == NULL)
			return (free_2d((void **)arr), NULL);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
