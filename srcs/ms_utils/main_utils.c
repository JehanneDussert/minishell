/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:17:29 by jdussert          #+#    #+#             */
/*   Updated: 2021/02/02 14:43:57 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_count_commands(int *count, char **buf)
{
	int i;

	i = 0;
	while (buf[i++])
	{
		*count += 1;
	}
}

void	ft_ctrl_c(char **save_if_ctrl_d)
{
	g_all.c = 0;
	(*save_if_ctrl_d)[0] = '\0';
}
