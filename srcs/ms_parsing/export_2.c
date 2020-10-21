/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:26:33 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/21 17:27:05 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	empty_tmp(t_all *all)
{
	t_lst	*tmp;

	tmp = all->alst;
	while (tmp)
	{
		tmp->tmp = 0;
		tmp = tmp->next;
	}
}
