/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_char_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:05:51 by jdussert          #+#    #+#             */
/*   Updated: 2021/01/28 12:50:50 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_replace(char **comm, char **new, int *i, int *j)
{
	if ((*comm)[*i] && (*comm)[*i] == 1)
		(*new)[*j] = ' ';
	else if ((*comm)[*i] && (*comm)[*i] == 2)
		(*new)[*j] = '<';
	else if ((*comm)[*i] && (*comm)[*i] == 3)
		(*new)[*j] = '>';
	else if ((*comm)[*i] && (*comm)[*i] == 4)
		(*new)[*j] = ';';
	else if ((*comm)[*i] && (*comm)[*i] == 5)
		(*new)[*j] = '|';
	else if ((*comm)[*i] && (*comm)[*i] == 6)
	{
		(*i)++;
		return ;
	}
	(*j)++;
	(*i)++;
}

int		ft_len(char **comm)
{
	int	len;

	len = 0;
	while (comm[len])
		len++;
	return (len);
}

int		ft_check_if_special_char(char **comm, int i, int s, int d)
{
	if (((s % 2 || d % 2) && is_charset((*comm)[i], ";|><")) ||
		(is_charset((*comm)[i], "\\") && is_charset((*comm)[i + 1], "><")
		&& !ft_check_bs(comm[0], i)))
		return (1);
	return (0);
}
