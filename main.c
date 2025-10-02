/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:19:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/30 17:09:29 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"
#include "execution/execution.h"
#include "parsing/parsing.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	free_cmd_list(t_cmd *cmd)
{
	t_cmd		*c;
	t_subcmd	*s;
	t_subcmd	*sn;
	t_cmd		*cn;

	c = cmd;
	while (c)
	{
		s = c->head;
		while (s)
		{
			if (s->in_fd != -1)
				close(s->in_fd);
			sn = s->next;
			free(s);
			s = sn;
		}
		cn = c->next;
		free(c);
		c = cn;
	}
}

void	print_mini(t_mini *nyan)
{
	int	i;
	int	j;

	i = 0;
	while (nyan->head)
	{
		printf("PIPE N%d---------------------------------------------------\n",
			i);
		printf("CMD: %s\n", nyan->head->head->cmd);
		printf("ARGS->\n");
		j = 0;
		while (nyan->head->head->args && nyan->head->head->args[j])
		{
			printf("\t%s\n", nyan->head->head->args[j]);
			j++;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_mini mini;
	char *input;
	char **pipes;
	int status;

	mini.head = NULL;
	mini.env = envp;
	mini.last_status = 0;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{ /* Ctrl+D */
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (!no_unclosed_quotes(input))
		{
			ft_dprintf(2, "OwO What's is this?: *notices syntax error: unclosed quotes*\n");
			free(input);
			continue ;
		}
		if (!no_forbidden_actions(input))
		{
			ft_dprintf(2, "MiNyanShell: unsupported operator (&&, ||, *)\n");
			free(input);
			continue ;
		}
		pipes = init_mini(&mini, input);
		if (!pipes)
		{
			perror("init_mini");
			free(input);
			continue ;
		}
		fill_mini(&mini, pipes);
		free_2d((void **)pipes);
		status = ft_execution(mini.head, &mini);
		mini.last_status = status;
		free_cmd_list(mini.head);
		mini.head = NULL;

		free(input);
	}
	return (0);
}