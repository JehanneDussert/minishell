/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 22:02:38 by ede-banv          #+#    #+#             */
/*   Updated: 2019/10/23 19:51:16 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		size_tab(int n)
{
	int m;
	int nb;

	m = 1;
	nb = n;
	if (nb < 0)
		m++;
	while (nb / 10 != 0)
	{
		nb /= 10;
		m++;
	}
	return (m);
}

static char		*ft_malloc(int n)
{
	int		m;
	char	*tab;

	m = size_tab(n);
	if (!(tab = malloc(sizeof(*tab) * (m + 1))))
		return (NULL);
	return (tab);
}

char			*ft_itoa(int n)
{
	int		nb;
	int		m;
	int		i;
	char	*res;

	m = size_tab(n);
	i = m - 1;
	nb = n;
	if (!(res = ft_malloc(n)))
		return (NULL);
	while (i >= 0)
	{
		if (n < 0)
			res[i--] = -(nb % 10) + 48;
		else
			res[i--] = (nb % 10) + 48;
		nb /= 10;
	}
	if (n < 0)
		res[0] = '-';
	res[m] = '\0';
	return (res);
}
