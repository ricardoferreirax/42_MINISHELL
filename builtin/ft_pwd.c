/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:31:07 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/01 11:34:33 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "builtin.h"
#include "../execution/execution.h"

static int	print_pwd_from_env(char **env)
{
	int	i;

	if (!env)
		return (1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			ft_putstr_fd(env[i] + 4, STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
			return (0);
		}
		i++;
	}
	ft_putstr_fd("MiNyanShell: pwd: PWD not set", STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int	ft_pwd(t_subcmd *subcmd, t_mini *mini)
{
	char	*cwd;
	int		status;

	if (subcmd->args[1] && subcmd->args[1][0] == '-')
	{
		ft_putstr_fd("MiNyanShell: pwd: options are not supported",
			STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
		mini->last_status = 1;
		return (1);
	}
	cwd = getcwd(NULL, 0); //
	if (!cwd)
	{
		status = print_pwd_from_env(mini->env);
		mini->last_status = status;
		return (status);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	mini->last_status = 0;
	return (0);
}
