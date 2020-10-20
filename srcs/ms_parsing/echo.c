/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:18:45 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/20 15:07:05 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_croch(char *comm)
{
	int	i;

	i = 1;
	while (comm[i] != '"')
		ft_putchar_fd(comm[i++], 1);
}

void	ft_echo(char **comm)
{
	int		i;
	char	*opt;

	i = 1;
	opt = "off";
	while (comm[i])
	{
		if (i == 1 && !ft_strncmp(comm[1], "-n", 2))
			opt = "-n";
		else if (comm[i][0] == '"')
			ft_echo_croch(comm[i]);
		else
			ft_putstr_fd(comm[i], 1);
		if (comm[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!ft_strncmp(opt, "off", 3))
		ft_putchar_fd('\n', 1);
}
