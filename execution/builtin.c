/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:07:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/02 15:16:04 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "../builtin/builtin.h"
#include "execution.h"
#include "../libft/libft.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (true);
	return (false);
}

int	execute_builtin(t_subcmd *subcmd, t_mini *mini)
{
	if (!subcmd || !subcmd->args || !subcmd->args[0])
	{
		mini->last_status = 1;
		return (1);
	}
	if (ft_strcmp(subcmd->args[0], "echo") == 0)
		return (ft_echo(subcmd));
	else if (ft_strcmp(subcmd->args[0], "pwd") == 0)
		return (ft_pwd(subcmd, mini));
	// else if (ft_strcmp(subcmd->args[0], "cd") == 0)
	//     return (ft_cd(mini, subcmd->args));
	// else if (ft_strcmp(subcmd->args[0], "export") == 0)
	//     return (ft_export(mini, subcmd->args));
	// else if (ft_strcmp(subcmd->args[0], "unset") == 0)
	//     return (ft_unset(mini, subcmd->args));
	else if (ft_strcmp(subcmd->args[0], "env") == 0)
	    return (ft_env_list(mini, subcmd));
	// else if (ft_strcmp(subcmd->args[0], "exit") == 0)
	//     return (ft_exit(mini, subcmd->args));
	mini->last_status = 1;
	return (1);
}
