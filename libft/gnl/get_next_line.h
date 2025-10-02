/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:42:45 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:19:55 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "fcntl.h"
# include "stdlib.h"
# include "unistd.h"

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int b);
char	*gnl_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*isolate_line(char *line, char *buffer);

#endif
