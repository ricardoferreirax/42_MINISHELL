/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:22:15 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/02 15:15:25 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "../environ/envyan.h"

// static int env_check_args(t_mini *mini, t_subcmd *subcmd)
// {
//     if (subcmd && subcmd->args && subcmd->args[1])
//     {
//         write(STDERR_FILENO, "env: ", 5);
//         write(STDERR_FILENO, subcmd->args[1], ft_strlen(subcmd->args[1]));
//         write(STDERR_FILENO, ": No such file or directory\n", 29);
//         if (mini) 
//             mini->last_status = 127;
//         return (127);
//     }
//     return 0;
// }

// int ft_env(t_mini *mini, t_subcmd *subcmd)
// {
//     int i;
//     int check;

//     check = env_check_args(mini, subcmd);
//     if (check != 0)
//         return (check);
//     if (!mini || !mini->env)
//     {
//         if (mini) mini->last_status = 0;
//         return (0);
//     }
//     i = 0;
//     while (mini->env[i])
//     {
//         if (ft_strchr(mini->env[i], '='))
//         {
//             write(STDOUT_FILENO, mini->env[i], ft_strlen(mini->env[i]));
//             write(STDOUT_FILENO, "\n", 1);
//         }
//         i++;
//     }
//     mini->last_status = 0;
//     return (0);
// }

static int env_check_args(t_mini *mini, t_subcmd *subcmd)
{
    if (subcmd && subcmd->args && subcmd->args[1])
    {
        write(STDERR_FILENO, "env: ", 5);
        write(STDERR_FILENO, subcmd->args[1], ft_strlen(subcmd->args[1]));
        write(STDERR_FILENO, ": No such file or directory\n", 29);
        if (mini) mini->last_status = 127;
        return 127;
    }
    if (mini) mini->last_status = 0;
    return 0;
}

int ft_env_list(t_mini *mini, t_subcmd *subcmd)
{
    t_envp *n;
    int     check;

    check = env_check_args(mini, subcmd);
    if (check != 0)
        return check;
    if (!mini || !mini->envyan_list)
        return 0;
    n = mini->envyan_list;
    while (n)
    {
        if (n->key && n->value)
        {
            write(STDOUT_FILENO, n->key, ft_strlen(n->key));
            write(STDOUT_FILENO, "=", 1);
            write(STDOUT_FILENO, n->value, ft_strlen(n->value));
            write(STDOUT_FILENO, "\n", 1);
        }
        n = n->next;
    }
    mini->last_status = 0;
    return 0;
}
