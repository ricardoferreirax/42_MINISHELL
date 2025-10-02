/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:36:57 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/27 08:21:44 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*buffer;
	int		sizesrc;

	if (!src)
		return (NULL);
	sizesrc = ft_strlen(src);
	buffer = malloc((sizesrc * sizeof(char)) + 1);
	if (buffer == NULL)
		return (NULL);
	ft_strcpy(buffer, src);
	return (buffer);
}
