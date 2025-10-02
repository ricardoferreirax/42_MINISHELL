/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:15:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/02 11:20:46 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "execution.h"

void	execute_external_cmd(t_subcmd *subcmd, t_mini *mini)
{
	char	*cmd_path;

	cmd_path = handle_cmd_path(subcmd->args[0], mini->env);
	if (!cmd_path)
	{
		cmd_not_found_msg(subcmd->args[0]);
		exit(127);
	}
	execve(cmd_path, subcmd->args, mini->env);
	perror("execve failed");
	free(cmd_path);
	if (errno == EACCES || errno == EISDIR)
		exit(126);
	else if (errno == ENOENT)
		exit(127);
	exit(EXIT_FAILURE);
}

int	run_external_single(t_subcmd *subcmd, t_mini *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("MiNyanshell: fork failed"), 1);
	if (pid == 0)
	{
		// set_child_signals();
		if (apply_redirs_in_child(subcmd) != 0)
			exit(1);
		if (!subcmd->args || !subcmd->args[0])
			exit(0);
		if (subcmd->args[0][0] == '\0')
		{
			cmd_not_found_msg(subcmd->args[0]);
			exit(127);
		}
		execute_external_cmd(subcmd, mini);
	}
	close_heredoc(subcmd);
	return (wait_for_single(pid));
}

int	run_redirs_without_cmd(t_cmd *cmd, t_mini *mini)
{
	t_subcmd	*sub;
	int			orig_stdin;
	int			orig_stdout;
	int			result;

	if (!cmd || !cmd->head)
		return (0);
	sub = cmd->head;
	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (orig_stdin == -1 || orig_stdout == -1)
		return (perror("MiNyanshell: dup original fds"), 1);
	result = apply_redirs_in_child(sub);
	reset_fds(orig_stdin, orig_stdout);
	if (sub->in_fd != -1)
	{
		close(sub->in_fd);
		sub->in_fd = -1;
	}
	mini->last_status = result;
	return (result);
}

int	execute_single_cmd(t_subcmd *subcmd, t_mini *mini)
{
	int	orig_stdin;
	int	orig_stdout;

	while(subcmd && subcmd->next)
	{
		if(subcmd->cmd)
			break;
		subcmd = subcmd->next;
	}
	if (!subcmd || !subcmd->args || !subcmd->args[0]
		|| !is_builtin(subcmd->args[0]))
		return (-1);
	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (orig_stdin == -1 || orig_stdout == -1)
		return (perror("MiNyanshell: dup original fds"), 1);
	if (apply_redirs_in_child(subcmd) != 0)
	{
		reset_fds(orig_stdin, orig_stdout);
		close_heredoc(subcmd);
		return (1);
	}
	execute_builtin(subcmd, mini);
	reset_fds(orig_stdin, orig_stdout);
	close_heredoc(subcmd);
	return (0);
}
