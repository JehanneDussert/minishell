/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 21:47:41 by emmadebanvi       #+#    #+#             */
/*   Updated: 2021/01/24 16:31:44 by marvin           ###   ########.fr       */
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

void	ft_exit_error(t_all *all, int mode)
{
	if (mode == 1)
	{
		all->exit->e = 2;
		error_msg("exit", "Numeric argument needed.");
	}
	else
	{
		all->exit->e = 1;
		error_msg("exit", "Too many arguments");
	}
}

void	ft_exit_fct(t_all *all, char **comm)
{
	int	i;

	i = 0;
	if (!comm[1])
	{
		all->err = 0;
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
				all->exit->e = makenumber(comm[1]);
			else
				ft_exit_error(all, 1);
		}
		else
			ft_exit_error(all, 2);
	}
}
