/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:25:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/01 09:18:02 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "../execution/execution.h"
#include <stdio.h>

void	error_exit(const char *message)
{
	perror(message);
	exit(1);
}

void	cmd_not_found_msg(char *cmd)
{
	ft_putstr_fd("MiNyanshell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
}

void	path_not_found_msg(char *cmd)
{
	ft_putstr_fd("MiNyanshell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void warn_heredoc_eof(char *lim)
{
    write(STDERR_FILENO,
          "warning: here-document delimited by end-of-file (wanted '", 58);
    write(STDERR_FILENO, lim, ft_strlen(lim));
    write(STDERR_FILENO, "')\n", 3);
}

void handle_fork_error(t_cmd *current_cmd, t_pipeline *pp)
{
    if (pp && pp->mini)
        pp->mini->last_status = 1;
    if (pp && pp->prev_pipefd != -1) /* fecha o read-end do pipe anterior, se ainda existir */
	{
        close(pp->prev_pipefd);
        pp->prev_pipefd = -1;
    }
    if (current_cmd && current_cmd->next && pp) /* se para este comando tínhamos criado um pipe, fecha as duas pontas */
	{
        close(pp->pipefd[0]);
        close(pp->pipefd[1]);
    }
    if (current_cmd && current_cmd->head)
        close_heredoc(current_cmd->head);
}
