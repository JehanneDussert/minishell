/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 21:47:41 by emmadebanvi       #+#    #+#             */
/*   Updated: 2021/01/04 18:43:26 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		makenumber(char *number)
{
	long int	nb;
	int			i;
	int			neg;
	int			res;

	nb = 0;
	i = (number[0] == '-' ? 1 : 0);
	neg = (number[0] == '-' ? 1 : 0);
	res = 0;
	while (number[i])
	{
		nb = nb * 10 + (number[i] - 48);
		i++;
	}
	nb = (neg == 1 ? nb * -1 : nb);
	if (nb >= 256)
		res = nb % 256;
	else if (nb < 0)
		res = 256 + (nb % 256);
	else
		res = nb;
	return (res);
}

void	ft_exit_fct(t_all *g_all, char **comm)
{
	int	i;

	i = 0;
	if (!comm[1])
	{
		g_all->exit->e = 0;
		return ;
	}
	else
	{
		if (!comm[2])
		{
			if (comm[1][i])
				i++;
			while (comm[1][i])
				if (!ft_isdigit(comm[1][i++]))
					break ;
			if (comm[1][i] == '\0')
				g_all->exit->e = makenumber(comm[1]);
			else
				g_all->exit->e = 2;
		}
		else
			error_msg("exit", "Too many arguments");
	}
}
