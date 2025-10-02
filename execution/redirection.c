/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:37:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/01 20:06:18 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "execution.h"

static int open_redir_file(char *filename, t_redir_type type)
{
    int fd;

    if (!filename)
        return (-1);
    if (type == REDIR_IN) 
        fd = open(filename, O_RDONLY);
    else if (type == REDIR_OUT)
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (type == REDIR_APPEND)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        return (-1);
    if (fd == -1)
        perror(filename);
    return (fd);
}

static int handle_input_redir(t_subcmd *node, int *last_in_fd)
{
    int fd;

    if (!node->infile)
        return (0);
    if (node->type == REDIR_IN || node->type == REDIR_INOUT) 
	{
        fd = open_redir_file(node->infile, REDIR_IN);
        if (fd == -1)
            return (1);
        if (*last_in_fd != -1 && *last_in_fd != node->in_fd) /* se já tínhamos um input anterior (e não é o heredoc ainda ativo), fecha-o */
            close(*last_in_fd);
        *last_in_fd = fd;
    }
    return (0);
}

static int handle_output_redir(t_subcmd *node, int *last_out_fd)
{
    int fd;

    if (!node->outfile)
        return (0);
    if (node->type == REDIR_OUT || node->type == REDIR_APPEND || node->type == REDIR_INOUT) 
	{
        if (node->type == REDIR_APPEND)
            fd = open_redir_file(node->outfile, REDIR_APPEND);
        else
            fd = open_redir_file(node->outfile, REDIR_OUT);
        if (fd == -1)
            return (1);
        if (*last_out_fd != -1)
            close(*last_out_fd);
        *last_out_fd = fd;
    }
    return (0);
}

static int process_redirs(t_subcmd *node, int *last_in_fd, int *last_out_fd)
{
    while (node)
    {
        if (node->in_fd != -1) 
		{
            if (*last_in_fd != -1)
                close(*last_in_fd);
            *last_in_fd = node->in_fd;
        }
        if (handle_input_redir(node, last_in_fd))
            return (1);
        if (handle_output_redir(node, last_out_fd))
            return (1);
        node = node->next;
    }
    return (0);
}

int apply_redirs_in_child(t_subcmd *sub)
{
    int last_in_fd;
    int last_out_fd;

	last_in_fd = -1;
	last_out_fd = -1;
    if (process_redirs(sub, &last_in_fd, &last_out_fd))
        return (1);
    if (last_in_fd != -1) 
	{
        if (safe_dup2_and_close(last_in_fd, STDIN_FILENO) != 0)
            return (perror("MiNyanshell: failed to redirect input"), 1);
    }
    if (last_out_fd != -1) 
	{
        if (safe_dup2_and_close(last_out_fd, STDOUT_FILENO) != 0)
            return (perror("MiNyanshell: failed to redirect output"), 1);
    }
    return (0);
}
