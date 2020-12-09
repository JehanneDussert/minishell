/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skips.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:10:35 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/19 11:42:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		skipspace(char *line, int *i)
{
	while (line[*i] == ' ')
	{
		(*i)++;
	}
	return (1);
}

void	ft_skip_redirection(char **comd, int *i)
{
	int	s;

	s = 0;
	while (is_charset(comd[0][*i], ">< "))
	{
		(*i)++;
		s += 1;
	}
	if (s > 0)
		while (comd[0][*i] && comd[0][*i] != ' ')
		{
			(*i)++;
			s = 0;
		}
}
