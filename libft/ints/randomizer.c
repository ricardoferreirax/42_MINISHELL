/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:51:10 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:17:16 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ints.h"

int	randomizer(void)
{
	volatile int	x;
	volatile char	y;
	static int		i;
	int				*k;
	unsigned int	entropy;

	x = 0;
	y = 0;
	k = (int *)malloc(sizeof(int));
	entropy = ((unsigned int)(uintptr_t)&x) ^ ((unsigned int)(uintptr_t)&y);
	entropy ^= i * 2654435761;
	entropy = (entropy >> (i % 5)) ^ (entropy << (i % 3));
	entropy += (unsigned int)((uintptr_t)k) * (unsigned int)((uintptr_t)&i);
	i += 17;
	free(k);
	return (entropy);
}
