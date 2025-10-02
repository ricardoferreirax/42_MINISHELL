/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:57:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/01 16:46:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "execution.h"

static int	extract_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

static void	wait_for_children(t_mini *mini, pid_t last_pid)
{
	int		status;
	pid_t	pid;

	status = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
		{
			if (errno == EINTR) // interrompido por sinal?
				continue ;       // tenta de novo
			else                // ECHILD - não há mais childs para esperar
				break ;
		}
		if (pid == last_pid)
			mini->last_status = extract_exit_code(status);
	}
}

static void	parent_pipe_control(t_cmd *cmd, t_pipeline *pp)
{
	if (pp->prev_pipefd != -1) // Fecha o read end do pipe anterior caso ainda esteja aberto
	{
		close(pp->prev_pipefd);
		pp->prev_pipefd = -1;
	}
	if (cmd->next)  // Se houver próximo comando mantemos o read end do pipe atual
	{
		close(pp->pipefd[1]);
		pp->prev_pipefd = pp->pipefd[0]; // assim o próximo comando vai ler do read end do pipe atual
	}
	else // último comando não precisa de guardar o prev_pipefd
		pp->prev_pipefd = -1;
	if (cmd->head)
		close_heredoc(cmd->head);
}

static int	create_pipe_and_fork(t_cmd *cmd, t_pipeline *pp)
{
	if (cmd->next && pipe(pp->pipefd) == -1)
	{
		perror("MiNyanshell: error creating pipe");
		if (pp->prev_pipefd != -1)
		{
			close(pp->prev_pipefd);
			pp->prev_pipefd = -1;
		}
		return (-1);
	}
	if (safe_fork(cmd, pp) != 0)
		return (-1);
	return (0);
}

int	execute_pipeline(t_cmd *cmds, t_mini *mini)
{
	t_pipeline	pp;
	t_cmd		*current_cmd;

	pp.pid = -1;
	pp.prev_pipefd = -1;
	pp.last_status = 0;
	pp.mini = mini;
	// set_non_interactive_signals();
	current_cmd = cmds;
	while (current_cmd)
	{
		if (create_pipe_and_fork(current_cmd, &pp) == -1)
			return (handle_fork_error(current_cmd, &pp), 1);
		if (pp.pid == 0)
			child_execute_cmd(current_cmd, &pp);
		else
			parent_pipe_control(current_cmd, &pp);
		current_cmd = current_cmd->next;
	}
	wait_for_children(mini, pp.pid);
	// set_interactive_signals();       voltar ao modo prompt
	return (mini->last_status);
}
