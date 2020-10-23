/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:18:45 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/23 17:39:38 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_env(char *comm, t_lst *alst, int err)
{
	int	i;

	i = 0;
	comm = ft_strtrim(comm, "{}");
	if (comm[0] == '?')
	{
		ft_putnbr_fd(err, 1);
		return ;
	}
	while (alst)
	{
		if(!ft_strcmp(comm, alst->key))
		{
			ft_putstr_fd(alst->content, 1);
			return ;
		}
		alst = alst->next;
	}
}

int		ft_echo_n(char *comm, char **opt)
{
	int i;

	i = 1;
	while (comm[i])
	{
		if (comm[i] != 'n')
			return (0);
		i++;
	}
	*opt = "-n";
	return (1);
}

void	ft_echo_quote(char *comm)
{
	int i;
	int		s;
	int		d;

	i = 0;
	s = 0;
	d = 0;
	while (comm[i])
	{
		if_in_quote(&d, &s, &i, comm);
		if (s == 1)
			while (comm[i] != '\'')
				ft_putchar_fd(comm[i++], 1);
		else if (d == 1)
			while (comm[i] != '\"')
				ft_putchar_fd(comm[i++], 1);
		i++;
	}
}

void	ft_init_echo(int *i, char **opt, int *s, int *d, int *res)
{
	*i = 1;
	*s = 0;
	*d = 0;
	*res = 0;
	*opt = "off";
}

void	ft_echo(char **comm, t_all *all)
{
	int		i;
	char	*opt;
	int		s;
	int		d;
	int		res;

	ft_init_echo(&i, &opt, &s, &d, &res);
	while (comm[i])
	{
		if (i == 1 && comm[i][0] == '-')
		{
			res = ft_echo_n(comm[i], &opt);
			if (res != 0)
				i++;
			res = 0;
		}
		if ((comm[i][0] == '"' || comm[i][0] == '\'') && !res)
			ft_echo_quote(comm[i]);
		else if (comm[i][0] == '$')
			ft_echo_env(&comm[i][1], all->alst, all->err);
		else
			ft_putstr_fd(comm[i], 1);
		if (comm[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!ft_strncmp(opt, "off", 3))
		ft_putchar_fd('\n', 1);
	all->err = 0;
}
