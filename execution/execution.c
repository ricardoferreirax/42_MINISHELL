/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:33:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/01 16:45:33 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "execution.h"
#include <readline/history.h>

static int	number_of_cmds(t_cmd *cmd_list)
{
	t_cmd	*current_cmd;
	int		num_cmds;

	if (!cmd_list)
		return (0);
	current_cmd = cmd_list;
	num_cmds = 0;
	while (current_cmd)
	{
		num_cmds++;
		current_cmd = current_cmd->next;
	}
	return (num_cmds);
}

static int	execute_cmds(t_cmd *cmd_list, t_mini *mini)
{
	int	num_cmds;
	int	status;

	num_cmds = number_of_cmds(cmd_list);
	if (num_cmds == 1)
	{
		status = execute_single_cmd(cmd_list->head, mini);
		if (status == -1)
			status = run_external_single(cmd_list->head, mini);
		return (status);
	}
	if (num_cmds > 1)
		return (execute_pipeline(cmd_list, mini));
	return (0); // num_cmds == 0 nada a executar
}

static int	pre_execution(t_cmd *cmd, t_mini *mini)
{
	t_subcmd	*sub;

	if (!cmd || !cmd->head)
		return (0);
	sub = cmd->head;
	if (process_all_heredocs(cmd, mini) != 0) // processa SEMPRE os heredocs se houver comandos/redirs
		return (1);
	if ((!sub->args || !sub->args[0]) && (sub->type != REDIR_INVALID) && !cmd->next) // só redireções (sem args e sem pipeline)
		return (run_redirs_without_cmd(cmd, mini));
	if ((!sub->args || !sub->args[0]) && (sub->type == REDIR_INVALID)) // comando vazio (sem args e sem redirs)
		return (0);
	return (-1); // it's totally fineeee
}

int	ft_execution(t_cmd *cmd_list, t_mini *mini)
{
	int	pre_exec;
	int	status;

	if (!mini || !cmd_list || !cmd_list->head)
	{
		if (mini)
			mini->last_status = 0;
		return (0);
	}
	// set_noninteractive_signals();
	pre_exec = pre_execution(cmd_list, mini);
	if (pre_exec != -1)
	{
		// set_signals();
		mini->last_status = pre_exec;
		return (pre_exec);
	}
	status = execute_cmds(cmd_list, mini);
	mini->last_status = status;
	// set_interactive_signals(); -> voltar ao modo prompt
	return (status);
}
