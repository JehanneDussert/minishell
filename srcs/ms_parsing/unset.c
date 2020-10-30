/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:56:12 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/26 11:54:32 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_catch_exp(char *cmd, t_all *all)
{
	t_lst	*before;
	t_lst	*tmp;

	tmp = all->alst;
	if (!ft_strcmp(cmd, tmp->key))
	{
		all->alst = all->alst->next;
		ft_lstdelone_ms(tmp, free);
		return ;
	}
	before = all->alst;
	tmp = before->next;
	while (tmp)
	{
		if (!ft_strcmp(cmd, tmp->key))
		{
			before->next = tmp->next;
			ft_lstdelone_ms(tmp, free);
			return ;
		}
		tmp = tmp->next;
		before = before->next;
	}
}

void	ft_unset(char **cmd, t_all *all)
{
	int i;
	int catch;

	i = 1;
	catch = 0;
	while (cmd[i])
	{
		if (!export_errors(cmd[i]))
		{
			catch = 1;
			all->err = 1;
		}
		else
			ft_catch_exp(cmd[i], all);
		i++;
	}
	if (catch == 0)
		all->err = 0;
}
