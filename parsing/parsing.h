/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:42:42 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/02 15:32:56 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../MiNyanShell.h"
# include <stdbool.h>

bool	no_unclosed_quotes(char *str);
bool	no_forbidden_actions(char *str);
char	**split_ignore_quotes(char *str, char sep);
char	**init_mini(t_mini *mini, char *input_line);
void	fill_mini(t_mini *mini, char **pipes);
void	fill_subcmd(t_cmd *node, char **tokens);
int		add_arg(t_subcmd *sub, const char *token);
int		arr_size(void **arr);
t_subcmd	*subcmd_new(void);
bool	is_redir(char *token);
char	*skip_whitespaces(char *str);
int		redir_append(t_subcmd **sub, t_redir_type redir_type, char *arg);
t_cmd	*cmd_new(void);
int		parse(t_subcmd **sub, char **tokens, int *i);

#endif
