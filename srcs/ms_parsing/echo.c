/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:18:45 by ede-banv          #+#    #+#             */
/*   Updated: 2021/01/28 14:29:58 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_one_char(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] == c)
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	ft_echo(char **comm, t_all *all)
{
	int		i;
	char	opt;
	int		res;

	ft_init_echo(&i, &opt, &res);
	while (comm[i] && comm[i][0] == '-' && ft_one_char(&comm[i][1], 'n'))
		i++;
	if (i > 1)
		opt = 1;
	while (comm[i])
	{
		ft_putstr_fd(comm[i], 1);
		if (comm[++i])
			ft_putchar_fd(' ', 1);
	}
	if (!opt)
		ft_putchar_fd('\n', 1);
	all->err = 0;
}
