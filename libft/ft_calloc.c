/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 20:30:49 by ede-banv          #+#    #+#             */
/*   Updated: 2019/10/24 23:30:34 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*r;
	size_t	i;

	i = 0;
	if (!size || !count)
	{
		size = 1;
		count = 1;
	}
	if (!(r = malloc(count * size)))
		return (NULL);
	while (i < (size * count))
	{
		*(char *)r = '\0';
		r++;
		i++;
	}
	return (r - i);
}
