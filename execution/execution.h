/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:22:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/01 19:58:37 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../MiNyanShell.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_UwU	t_mini;
typedef struct s_0w0	t_subcmd;

typedef struct s_pipeline
{
	pid_t				pid;
	int					pipefd[2];
	int					prev_pipefd;
	int					last_status;
	t_mini				*mini;
}						t_pipeline;

int						ft_execution(t_cmd *cmd_list, t_mini *mini);
int						execute_single_cmd(t_subcmd *subcmd, t_mini *mini);
int						run_external_single(t_subcmd *subcmd, t_mini *mini);
void					execute_external_cmd(t_subcmd *subcmd, t_mini *mini);
int						execute_pipeline(t_cmd *cmd_list, t_mini *mini);
void					child_execute_cmd(t_cmd *cmd, t_pipeline *pp);
int						run_redirs_without_cmd(t_cmd *cmd, t_mini *mini);
int						apply_redirs_in_child(t_subcmd *sub);
char					*handle_cmd_path(char *cmd, char **envp);
bool					is_builtin(char *cmd);
int						execute_builtin(t_subcmd *subcmd, t_mini *mini);
int						process_all_heredocs(t_cmd *cmd_list, t_mini *mini);
int						handle_single_heredoc(t_subcmd *subcmd, t_mini *mini);
int						safe_dup2_and_close(int oldfd, int newfd);
void					reset_fds(int stdin_fd, int stdout_fd);
void					close_heredoc(t_subcmd *subcmd);
int						safe_fork(t_cmd *cmd, t_pipeline *pp);
void					handle_fork_error(t_cmd *current_cmd, t_pipeline *pp);
int						wait_for_single(pid_t pid);
char					**ft_split_quotes(char const *s, char c);
void					free_args(char **args);
void					warn_heredoc_eof(char *lim);
void					ft_free_str(char **str);
void					cmd_not_found_msg(char *cmd);
void	error_exit(const char *message);


void					free_chararr(char **arr);

#endif