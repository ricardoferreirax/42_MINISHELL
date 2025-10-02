/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_subcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:56:45 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/01 18:04:37 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "parsing.h"

t_subcmd	*subcmd_new(void)
{
	t_subcmd	*subcmd;

	subcmd = (t_subcmd *)calloc(1, sizeof(*subcmd));
	if (!subcmd)
		return (NULL);
	subcmd->type = REDIR_INVALID;
	subcmd->args = NULL;
	subcmd->cmd = NULL;
	subcmd->delimiter = NULL;
	subcmd->outfile = NULL;
	subcmd->infile = NULL;
	subcmd->in_fd = -1;
	subcmd->out_fd = -1;
	subcmd->next = NULL;
	return (subcmd);
}

int	add_arg(t_subcmd *subcmd, const char *token)
{
	int		count;
	int		i;
	char	**new_arg;

	if (!subcmd || !token)
		return (1);
	count = 0;
	if (subcmd->args)
	{
		while (subcmd->args[count])
			count++;
	}
	new_arg = (char **)malloc((count + 2) * sizeof(char *));
	if (!new_arg)
		return (1);
	i = 0;
	while (i < count) // copia osponteiros antigos
	{
		new_arg[i] = subcmd->args[i];
		i++;
	}
	new_arg[count] = ft_strdup(token);
	if (!new_arg[count])
	{
		free(new_arg);
		return (1);
	}
	new_arg[count + 1] = NULL;
	if (subcmd->args)
		free(subcmd->args);
	subcmd->args = new_arg;
	if (!subcmd->cmd)
	{
		subcmd->cmd = ft_strdup(token);
		if (!subcmd->cmd)
			return (1);
	}
	return (0);
}

void	fill_subcmd(t_cmd *node, char **tokens)
{
	t_subcmd	*head;
	t_subcmd	*curr;
	int			i;

	head = subcmd_new();
	if (!head)
		return ;
	curr = head;
	i = 0;
	while (tokens[i])
	{
		if (!parse(&curr, tokens, &i))
			break ;
	}
	node->head = head;
}
