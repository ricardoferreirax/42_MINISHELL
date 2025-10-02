/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:08:08 by pfreire-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/09/25 13:27:36 by pfreire-         ###   ########.fr       */
=======
/*   Updated: 2025/10/01 11:53:40 by pfreire-         ###   ########.fr       */
>>>>>>> ricardo
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "parsing.h"
<<<<<<< HEAD
#include <stdbool.h>

char	*skip_whitespaces(char *str)
{
	if (str == NULL)
		return (NULL);
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	return (str);
}

int	count_words_ignore_quotes(char *str, char c)
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

char	*word_copy_ignorequotes(char **s, char c)
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

bool	no_unclosed_quotes(char *str)
{
	bool	inquote;
	bool	indquote;
	int		i;

	inquote = false;
	indquote = false;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		i++;
	}
	if (indquote || inquote)
		return (false);
	return (true);
}
=======

>>>>>>> ricardo

bool	forbidden_instruction(char *str, int i)
{
	if (str[i] == '&')
	{
		if (str[i + 1] == '&')
			return (true);
	}
	else if (str[i] == '|')
	{
		if (str[i + 1] == '|')
			return (true);
	}
	else if (str[i] == '*')
	{
		return (true);
	}
	return (false);
}

<<<<<<< HEAD
bool	no_forbidden_actions(char *str)
{
	int		i;
	bool	inquote;
	bool	indquote;

	i = 0;
	inquote = false;
	indquote = false;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		if (!forbidden_instruction(str, i) && !indquote && !inquote)
			return (false);
		i++;
	}
	return (true);
}

t_redir_type	which_type(t_subcmd *cmd, char **argv, int i)
{
	if (ft_strcmp(argv[i], "<<") == 0)
	{
		cmd->delimiter = ft_strdup(argv[i + 1]);
		return (REDIR_HEREDOC);
	}
	if (ft_strcmp(argv[i], ">>"))
	{
		cmd->outfile = ft_strdup(argv[i + 1]);
		return (REDIR_APPEND);
	}
	if (ft_strcmp(argv[i], "<"))
	{
		cmd->infile = ft_strdup(argv[i]);
		return (REDIR_IN);
	}
	if (ft_strcmp(argv[i], ">"))
	{
		cmd->outfile = argv[i + 1];
		return (REDIR_OUT);
	}
	return (REDIR_INVALID);
}

=======

char	*skip_whitespaces(char *str)
{
	if (str == NULL)
		return (NULL);
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	return (str);
}

int arr_size(void **arr)
{
    int i;

    i = 0;
    if (!arr) 
        return (0);
    while (arr[i]) 
        i++;
    return (i);
}

t_cmd *cmd_new(void)  // cria um nó de comando (um elemento da pipeline!)
{
    t_cmd *cmd = (t_cmd *)calloc(1, sizeof(*cmd));
    if (!cmd) 
        return (NULL);
    cmd->head = NULL;
    cmd->next = NULL;
    // cmd->pipe = false;
    return (cmd);
}
>>>>>>> ricardo
