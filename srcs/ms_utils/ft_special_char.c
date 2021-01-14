/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:47:39 by jehannedu         #+#    #+#             */
/*   Updated: 2021/01/14 16:04:54 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cmd_fill(char **comd, char ***tmp, int *i, int *j)
{
	(*tmp)[0][*j] = comd[0][*i];
	(*j)++;
	(*i)++;
}

int		ft_env_in_quote(char *comd)
{
	int	i;
	int	d;
	int res;

	i = 0;
	d = 0;
	res = 0;
	while (comd[i])
	{
		if (comd[i] == '\"')
			d++;
		else if (comd[i] == '$' && d == 1 && res == 0)
			res++;
		if (d == 2 && res == 1)
			return (1);
		i++;
	}
	return (0);
}
