/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:34:19 by ede-banv          #+#    #+#             */
/*   Updated: 2019/10/24 23:14:38 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_mallocstr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	char	*res;

	j = 0;
	while (j < len && start < ft_strlen(s) && s[start])
	{
		j++;
		start++;
	}
	if (!(res = malloc(sizeof(*res) * (j + 1))))
		return (NULL);
	return (res);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	if (!(res = ft_mallocstr(s, start, len)))
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (i < len && s[start])
			res[i++] = s[start++];
	}
	res[i] = '\0';
	return (res);
}
