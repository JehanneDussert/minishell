/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:17:29 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/26 14:18:57 by jdussert         ###   ########.fr       */
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
