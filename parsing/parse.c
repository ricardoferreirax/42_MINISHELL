/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:24:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/30 17:17:07 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "parsing.h"

int	parse(t_subcmd **sub, char **tokens, int *i)
{
	char	*op;
	t_subcmd *curr = *sub;

	if (tokens[*i] && !is_redir(tokens[*i]))
	{
		if (!curr->cmd)
		{
			curr->cmd = ft_strdup(tokens[*i]);
			if (!curr->cmd)
				return (0);
		}
		while (tokens[*i] && !is_redir(tokens[*i]))
		{
			if (add_arg(curr, tokens[*i]) != 0)
				return (0);
			(*i)++;
		}
		return (1);
	}
	if (tokens[*i] && is_redir(tokens[*i]))
	{
		op = tokens[*i];
		(*i)++;
		if (!tokens[*i] || is_redir(tokens[*i]))
			return (0); /* operador sem alvo */
		if (ft_strcmp(op, "<<") == 0)
		{
			if (redir_append(sub, REDIR_HEREDOC, tokens[*i]) != 0)
				return (0);
		}
		else if (ft_strcmp(op, "<") == 0)
		{
			if (redir_append(sub, REDIR_IN, tokens[*i]) != 0)
				return (0);
		}
		else if (ft_strcmp(op, ">>") == 0)
		{
			if (redir_append(sub, REDIR_APPEND, tokens[*i]) != 0)
				return (0);
		}
		else if (ft_strcmp(op, ">") == 0)
		{
			if (redir_append(sub, REDIR_OUT, tokens[*i]) != 0)
				return (0);
		}
		(*i)++;
		//*sub = curr;
		return (1);
	}
	return (0);
}
