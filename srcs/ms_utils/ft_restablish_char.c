/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restablish_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 20:57:56 by jehannedu         #+#    #+#             */
/*   Updated: 2021/01/26 12:44:13 by jdussert         ###   ########.fr       */
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

void	ft_restablish_char(char ***comm)
{
	int		i;
	int		j;
	int		k;
	char	**new;

	k = 0;
	if ((new = ft_calloc(ft_len((*comm)) + 1, sizeof(char *))) == NULL)
		return ;
	while ((*comm)[k])
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
		k++;
	}
	free_read(comm, NULL);
	k = 0;
	if (((*comm) = ft_calloc(ft_len(new) + 1, sizeof(char *))) == NULL)
		return ;
	while (new[k])
	{
		(*comm)[k] = ft_strdup(new[k]);
		k++;
	}
	free_read(&new, NULL);
}

void	ft_restablish_redir(char ***comm, t_all *all)
{
	int		i;
	int		j;
	int		k;
	char	**new;

	k = 0;
	(void)all;
	if ((new = ft_calloc(ft_len((*comm)) + 1, sizeof(char *))) == NULL)
		return ;
	while ((*comm)[k])
	{
		i = 0;
		j = 0;
		if ((new[k] = ft_calloc(ft_strlen((*comm)[k]) + 1,
			sizeof(char))) == NULL)
			return ;
		while ((*comm)[k][i])
		{
			if ((*comm)[k][i] == 1 || (*comm)[k][i] == 2
				|| (*comm)[k][i] == 3)
				ft_replace(&((*comm)[k]), &new[k], &i, &j);
			else
				new[k][j++] = (*comm)[k][i++];
		}
		k++;
	}
	free_read(comm, NULL);
	k = 0;
	if (((*comm) = ft_calloc(ft_len(new) + 1, sizeof(char *))) == NULL)
		return ;
	while (new[k])
	{
		(*comm)[k] = ft_strdup(new[k]);
		k++;
	}
	free_read(&new, NULL);
}
