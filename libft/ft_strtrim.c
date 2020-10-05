/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:49:17 by ede-banv          #+#    #+#             */
/*   Updated: 2019/10/24 23:17:30 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_set(char c, char const *set)
{
	int i;

	i = 0;
	if (!set)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int		lnewstr(char const *s1, char const *set)
{
	int i;
	int j;
	int len;

	i = 0;
	len = 0;
	while (check_set(s1[i], set) && s1[i])
		i++;
	while (s1[len])
		len++;
	if (len == 0 || len == i)
		return (0);
	j = len;
	while (j > 0 && check_set(s1[j - 1], set))
		j--;
	len = j - i;
	return (len);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*tab;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	len = lnewstr(s1, set);
	i = 0;
	j = 0;
	if (!(tab = malloc(sizeof(*tab) * (len + 1))))
		return (NULL);
	while (check_set(s1[i], set))
		i++;
	while (j < len)
	{
		tab[j] = s1[j + i];
		j++;
	}
	tab[j] = '\0';
	return (tab);
}
