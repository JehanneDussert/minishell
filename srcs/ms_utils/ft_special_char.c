/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehannedussert <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:47:39 by jehannedu         #+#    #+#             */
/*   Updated: 2021/01/04 15:47:41 by jehannedu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_nb_backslash(char *comd)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (comd[i])
	{
		if (is_charset(comd[i], "\\"))
		{
			nb++;
			if (i > 0 && comd[i - 1] == '\\' && nb % 2 == 0)
				g_all.bs++;
		}
		i++;
	}
}

void	ft_check_hash(char ***commands)
{
	int	i;

	i = 0;
	while ((*commands)[0][i] && g_all.quote != 1)
	{
		if ((*commands)[0][0] == '#' ||
			(i > 0 && (*commands)[0][i - 1] == ' ' && (*commands)[0][i] == '#'))
		{
			(*commands)[0] = ft_return_new_comd(commands[0],
			&(*commands)[0][i]);
			if ((*commands)[1])
				free_read(NULL, &(*commands)[1]);
			return ;
		}
		if ((*commands)[0][i] == '\\')
			((*commands)[0] = ft_return_new_comd(&(*commands)[0], "\\"));
		i++;
	}
}

void	ft_hash(char **comd, char ***tmp, int *i, int *j)
{
	(*tmp)[0][*j] = comd[0][*i];
	(*j)++;
	(*i)++;
}

void	ft_backslash(char **comd, char ***tmp, int *i, int *j)
{
	ft_putendl_fd("enter", 2);
	if (g_all.bs == 0)
		while (comd[0][*i])
		{
			if (comd[0][*i] != '\\')
			{
				(*tmp)[0][*j] = comd[0][*i];
				(*j)++;
			}
			(*i)++;
		}
	else if (comd[0][*i + 1])
		while (comd[0][++(*i)])
		{
			(*tmp)[0][*j] = comd[0][*i];
			(*j)++;
		}
}
