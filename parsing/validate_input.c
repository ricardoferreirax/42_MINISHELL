/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:46:47 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/30 17:12:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "parsing.h"

bool no_forbidden_actions(char *str)
{
    int  i;
    bool in_squote;
    bool in_dquote;

    if (!str)
        return true;
    i = 0;
    in_squote = false;
    in_dquote = false;

    while (str[i] != '\0')
    {
        if (str[i] == '\'' && !in_dquote)
            in_squote = !in_squote;
        else if (str[i] == '\"' && !in_squote)
            in_dquote = !in_dquote;
        if (!in_squote && !in_dquote)
        {
            if (str[i] == '&' && str[i + 1] == '&')
                return false;   /* && proibido */
            if (str[i] == '|' && str[i + 1] == '|')
                return false;   /* || proibido */
            /* '*' é permitido; se quiseres bloquear, usa a variante B */
        }
        i++;
    }
    return true; /* não encontrou operadores proibidos */
}

bool	no_unclosed_quotes(char *str)
{
	bool	inquote;
	bool	indquote;
	int		i;

	inquote = false;
	indquote = false;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		i++;
	}
	if (indquote || inquote)
		return (false);
	return (true);
}