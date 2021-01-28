/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:47:39 by jehannedu         #+#    #+#             */
/*   Updated: 2021/01/28 15:27:51 by jdussert         ###   ########.fr       */
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

int		is_in_quote(char **comm, int index)
{
	int i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	while (i < index)
	{
		if ((*comm)[i] == '\"' && s % 2)
			d += 2;
		else if ((*comm)[i] == '\"' && ft_check_bs((*comm), i - 1))
			d++;
		else if ((*comm)[i] == '\'' && d % 2)
			s += 2;
		else if ((*comm)[i] == '\'')
			s++;
		i++;
	}
	if (d % 2 || s % 2)
		return (1);
	return (0);
}
