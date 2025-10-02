/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:00:40 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:33:34 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRINGS_H
# define FT_STRINGS_H

# include "../memory/memory.h"
# include "stdbool.h"
# include "stdlib.h"
# include "unistd.h"

int				ft_count_words(char const *s, char c);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int b);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strdup(const char *src);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
unsigned int	ft_strlcat(char *dest, const char *src, size_t size);
unsigned int	ft_strlcpy(char *dest, const char *scr, size_t size);
size_t			ft_strlen(const char *str);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *str, const char *to_find, size_t n);
char			*ft_strrchr(const char *a, int b);
char			*ft_strtrim(const char *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_wordcpy(const char **s, char c);

#endif