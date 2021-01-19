/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:47:39 by jehannedu         #+#    #+#             */
/*   Updated: 2021/01/19 15:27:18 by jdussert         ###   ########.fr       */
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
/*
void	ft_special_char(char **comm, char ***new, t_copy *copy)
{
	if (is_charset(comm[0][copy->i], "><|;"))
	{
		if (is_charset(comm[0][copy->i], "<"))
			(*new)[0][copy->j] = 2;
		else if (is_charset(comm[0][copy->i], ">"))
			(*new)[0][copy->j] = 3;
		else if (is_charset(comm[0][copy->i], ";"))
			(*new)[0][copy->j] = 4;
		else if (is_charset(comm[0][copy->i], "|"))
			(*new)[0][copy->j] = 5;
		copy->j++;
		copy->i++;
	}
}*/
