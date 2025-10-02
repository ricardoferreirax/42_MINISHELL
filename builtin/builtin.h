/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:17:37 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/02 15:15:41 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../MiNyanShell.h"
# include <stdlib.h>
# include <unistd.h>

int		ft_echo(t_subcmd *subcmd);
int		ft_pwd(t_subcmd *subcmd, t_mini *mini);
// int		ft_env(t_mini *mini, t_subcmd *subcmd);
int     ft_env_list(t_mini *mini, t_subcmd *subcmd);

bool	is_builtin(char *cmd);
int		execute_builtin(t_subcmd *subcmd, t_mini *mini);

#endif