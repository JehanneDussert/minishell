/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:18:45 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/20 15:42:16 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_n(char *comm, char **opt)
{
	int i;

	i = 1;
	while (comm[i])
	{
		if (comm[i] != 'n')
			return ;
		i++;
	}
	*opt = "-n";
}

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
		if (i == 1 && comm[i][0] == '-')
			ft_echo_n(comm[i], &opt);
		else if (comm[i][0] == '"')
			ft_echo_croch(comm[i]);
		else
			ft_putstr_fd(comm[i], 1);
		if (comm[i + 1] && ft_strcmp(opt, "-n") != 0)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!ft_strncmp(opt, "off", 3))
		ft_putchar_fd('\n', 1);
}
