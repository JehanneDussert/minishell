/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:39:27 by ede-banv          #+#    #+#             */
/*   Updated: 2019/10/24 17:55:56 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned int	r;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		r = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (r != '\0')
			return (r);
		i++;
	}
	return (0);
}
