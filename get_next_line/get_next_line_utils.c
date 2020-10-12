/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:54:08 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/12 16:43:44 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tab;
	size_t			i;

	i = 0;
	if (size == 0 && count == 0)
	{
		size = 1;
		count = 1;
	}
	if (!(tab = (unsigned char *)malloc(size * count)))
		return (NULL);
	while (i < count * size)
	{
		tab[i] = '\0';
		i++;
	}
	return (tab);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	if (!(res = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1)))
		return (NULL);
	i = 0;
	while (*s1)
	{
		res[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		res[i] = *s2;
		s2++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*dst;
	size_t		i;
	size_t		s_len;

	i = 0;
	if (s)
	{
		s_len = ft_strlen((char *)s);
		if ((dst = (char *)ft_calloc(len + 1, sizeof(*dst))) == NULL)
			return (NULL);
		if (start < s_len)
			while (i < len && s[start])
				dst[i++] = s[start++];
		return (dst);
	}
	else
		return (NULL);
}
