/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 21:17:26 by ede-banv          #+#    #+#             */
/*   Updated: 2019/10/18 21:17:42 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d;

	i = 0;
	d = ft_strlen(dst);
	if (d > dstsize)
		return (ft_strlen(src) + dstsize);
	dstsize -= d;
	while (src[i] && dstsize > 1)
	{
		dst[d + i] = src[i];
		i++;
		dstsize--;
	}
	dst[d + i] = '\0';
	return (d + ft_strlen(src));
}
