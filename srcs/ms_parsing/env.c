/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:36:19 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/26 11:37:01 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_id(char **comm, t_all *all)
{
	t_lst	*tmp;

	tmp = all->alst;
	if (!comm[1])
	{
		while (tmp)
		{
			if (tmp->content)
				print_line(tmp, 0);
			tmp = tmp->next;
		}
		empty_tmp(all);
	}
	all->err = 0;
}
