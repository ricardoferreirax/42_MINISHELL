/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:11:42 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/01 09:18:23 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "../execution/execution.h"

int wait_for_single(pid_t pid)
{
   int status;

    while (1)
    {
        if (waitpid(pid, &status, 0) == -1)
        {
            if (errno == EINTR)
                continue;     // tentou de novo se foi interrompido por sinal
            perror("MiNyanShell: waitpid");
            return (1);
        }
        break; // sai do loop se waitpid teve sucesso
    }
    if (WIFEXITED(status))   
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status)) 
        return (128 + WTERMSIG(status));
    return (1);
}

int safe_dup2_and_close(int oldfd, int newfd)
{
    if (oldfd < 0)
        return (0);
    if (oldfd != newfd)
    {
        if (dup2(oldfd, newfd) == -1)
        {
            perror("minishell: dup2 error");
            close(oldfd);
            return (1);
        }
    }
    close(oldfd);
    return (0);
}

void reset_fds(int stdin_fd, int stdout_fd)
{
    if (dup2(stdin_fd, STDIN_FILENO) == -1)
        perror("MiNyanshell: dup2 restore stdin");
    close(stdin_fd);

    if (dup2(stdout_fd, STDOUT_FILENO) == -1)
        perror("MiNyanshell: dup2 restore stdout");
    close(stdout_fd);
}

void close_heredoc(t_subcmd *subcmd)
{
    if (subcmd->in_fd != -1) // heredoc já foi processado e tem fd aberto
    {
        close(subcmd->in_fd);
        subcmd->in_fd = -1;
    }
}

int safe_fork(t_cmd *cmd, t_pipeline *pp)
{
    pp->pid = fork();
    if (pp->pid == -1)
    {
        perror("MiNyanshell: error forking process");
        if (cmd->next)
        {
            close(pp->pipefd[0]);
            close(pp->pipefd[1]);
        }
        if (pp->prev_pipefd != -1)
        {
            close(pp->prev_pipefd);
            pp->prev_pipefd = -1;
        }
        return (-1);
    }
    return (0);
}

void free_args(char **args)
{
    int i;

    if (!args)
        return;
    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

void	ft_free_str(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}