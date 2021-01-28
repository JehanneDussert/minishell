/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restablish_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 20:57:56 by jehannedu         #+#    #+#             */
/*   Updated: 2021/01/28 11:33:05 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_restablish_comd(char ***comm, char ***new)
{
	int	i;

	i = 0;
	if (((*comm) = ft_calloc(ft_len(*new) + 1, sizeof(char *))) == NULL)
		return ;
	while ((*new)[i])
	{
		(*comm)[i] = ft_strdup((*new)[i]);
		i++;
	}
	free_read(new, NULL);
}

void	ft_restablish_char(char ***comm)
{
	int		i;
	int		j;
	int		k;
	char	**new;

	k = -1;
	if ((new = ft_calloc(ft_len((*comm)) + 1, sizeof(char *))) == NULL)
		return ;
	while ((*comm)[++k])
	{
		i = 0;
		j = 0;
		if ((new[k] = ft_calloc(ft_strlen((*comm)[k]) + 1,
			sizeof(char))) == NULL)
			return ;
		while ((*comm)[k][i])
		{
			if ((*comm)[k][i] == 4 || (*comm)[k][i] == 5)
				ft_replace(&((*comm)[k]), &new[k], &i, &j);
			else
				new[k][j++] = (*comm)[k][i++];
		}
	}
	free_read(comm, NULL);
	ft_restablish_comd(comm, &new);
}

void	ft_restablish_redir(char ***comm)
{
	int		i;
	int		j;
	int		k;
	char	**new;

	k = -1;
	if ((new = ft_calloc(ft_len((*comm)) + 1, sizeof(char *))) == NULL)
		return ;
	while ((*comm)[++k])
	{
		i = 0;
		j = 0;
		if ((new[k] = ft_calloc(ft_strlen((*comm)[k]) + 1,
			sizeof(char))) == NULL)
			return ;
		while ((*comm)[k][i])
			if ((*comm)[k][i] == 1 || (*comm)[k][i] == 2
				|| (*comm)[k][i] == 3 || (*comm)[k][i] == 6)
				ft_replace(&((*comm)[k]), &new[k], &i, &j);
			else
				new[k][j++] = (*comm)[k][i++];
	}
	free_read(comm, NULL);
	ft_restablish_comd(comm, &new);
}
