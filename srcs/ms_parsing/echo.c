/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:18:45 by ede-banv          #+#    #+#             */
/*   Updated: 2021/01/27 16:33:35 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_echo_n(char *comm, char **opt)
{
	int i;

	i = 1;
	while (comm[i])
	{
		if (comm[i] != 'n' && comm[i] != '-' && comm[i] != ' ')
			return (0);
		i++;
	}
	*opt = "-n";
	return (i);
}

void	ft_check_n(int *i, int *res, char *comm, char **opt)
{
	*res = ft_echo_n(comm, opt);
	if (*res != 0)
		(*i)++;
	*res = 0;
}

void	ft_echo(char **comm, t_all *all)
{
	int		i;
	int		j;
	char	*opt;
	int		res;

	ft_init_echo(&i, &opt, &res);
	while (comm[i])
	{
		j = 0;
		if (comm[i][j] == '-' && (i == 1 || opt[0] == '-'))
			ft_check_n(&i, &res, comm[i], &opt);
		if (comm[i][j] != '-' || !ft_strncmp(opt, "off", 3))
			while (comm[i][j] && comm[i][j] != 1)
				ft_putchar_fd(comm[i][j++], 1);
		if (comm[i + 1] && ft_strncmp(opt, "-n", 2))
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!ft_strncmp(opt, "off", 3))
		ft_putchar_fd('\n', 1);
	all->err = 0;
}
