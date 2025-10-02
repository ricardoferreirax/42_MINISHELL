/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:44:25 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/02 14:51:09 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "envyan.h"

void free_envyan_list(t_envp *head)
{
    t_envp *tmp;

    while (head)
    {
        tmp = head->next;
        if (head->key)
            free(head->key);
        if (head->value)
            free(head->value);
        free(head);
        head = tmp;
    }
}

t_envp *envyan_node_new(void)
{
    t_envp *new_node;

    new_node = malloc(sizeof(t_envp));
    if (!new_node)
        return (NULL);
    new_node->key = NULL;
    new_node->value = NULL;
    new_node->next = NULL;
    return (new_node);
}

t_envp *envyan_node(char *envyan)
{
    t_envp *node;
    char *equal_sign;

    if (!envyan)
        return (NULL);
    node = envyan_node_new();
    if (!node)
        return (NULL);
    equal_sign = ft_strchr(envyan, '=');
    if (!equal_sign)
    {
        node->key = ft_strdup(envyan);
        if (!node->key)
        {
            free(node);
            return (NULL);
        }
        node->value = NULL;
        return (node);
    }
    node->key = ft_substr(envyan, 0, equal_sign - envyan);
    if (!node->key)
    {
        free(node);
        return (NULL);
    }
    node->value = ft_strdup(equal_sign + 1);
    if (!node->value)
    {
        free(node->key);
        free(node);
        return (NULL);
    }
    return (node);
}

void envyan_node_add_back(t_envp **head, t_envp *new_node)
{
    t_envp *tmp;

    if (!head || !new_node)
        return ;
    if (!*head)
    {
        *head = new_node;
        return ;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

t_envp *envyan_list(char **envyan)
{
    t_envp *head;
    t_envp *node;
    int i;

    head = NULL;
    i = 0;
    while (envyan && envyan[i])
    {
        node = envyan_node(envyan[i]);
        if (!node)
        {
            free_envyan_list(head);
            return (NULL);
        }
        envyan_node_add_back(&head, node);
        i++;
    }
    return (head);
}
