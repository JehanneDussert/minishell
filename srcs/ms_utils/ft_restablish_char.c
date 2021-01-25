/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restablish_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 20:57:56 by jehannedu         #+#    #+#             */
/*   Updated: 2021/01/25 14:40:08 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_replace(char *comm, char **new, int *i, int *j)
{
	if (comm[*i] && comm[*i] == 1)
		new[0][*j] = ' ';
	else if (comm[*i] && comm[*i] == 2)
		new[0][*j] = '<';
	else if (comm[*i] && comm[*i] == 3)
		new[0][*j] = '>';
	else if (comm[*i] && comm[*i] == 4)
		new[0][*j] = ';';
	else if (comm[*i] && comm[*i] == 5)
		new[0][*j] = '|';
	(*j)++;
	(*i)++;
}

void	ft_restablish_char(char ***comm)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if ((new = ft_calloc(ft_strlen((*comm)[0]) + 1, sizeof(char))) == NULL)
		return ;
	while ((*comm)[0][i])
	{
		if ((*comm)[0][i] == 4 || (*comm)[0][i] == 5)
			ft_replace((*comm)[0], &new, &i, &j);
		else
		{
			new[j] = (*comm)[0][i];
			i++;
			j++;
		}
	}
	free_read(NULL, *comm);
	if (new)
	{
		(*comm)[0] = ft_strdup(new);
		ft_free((void **)&new);
	}
}

void	ft_restablish_redir(char ***comm, t_all *all)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if ((new = ft_calloc(all->cmd_len + 1, sizeof(char))) == NULL)
		return ;
	while ((*comm)[0][i])
	{
		if ((*comm)[0][i] == 2 || (*comm)[0][i] == 3)
			ft_replace((*comm)[0], &new, &i, &j);
		else
			new[j++] = (*comm)[0][i++];
	}
	free_read(NULL, *comm);
	if (new)
	{
		(*comm)[0] = ft_strdup(new);
		ft_free((void **)&new);
	}
}
