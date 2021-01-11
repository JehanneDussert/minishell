/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:18:45 by ede-banv          #+#    #+#             */
/*   Updated: 2021/01/11 14:44:34 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_env(char *comm, t_lst *alst, int err, int *i)
{
	char	*tmp;
	int		j;

	(*i) += 1;
	tmp = comm;
	while (comm[*i])
	{
		
		j = *i;
		while (comm[*i] == '?' || comm[*i] == '{' || comm[*i] == '$')
		{
			if (comm[*i] == '?')
				ft_putnbr_fd(err, 1);
			j++;
			(*i)++;
		}
		while (comm[*i] && comm[*i] != ' ' && comm[*i] != '$' && comm[*i] != '\'' &&
			comm[*i] != '\"' && comm[*i] != '=' && comm[*i] != '\\' &&
			comm[*i] && comm[*i] != '}')
			(*i)++;
		
		tmp = ft_substr(comm, j, ((*i - j)));
		ft_check_env(alst, &tmp);
		if (comm[*i] == '\"')
			return ;
	}
}

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

void	ft_echo_quote(char *comm)
{
	int i;
	int	s;
	int	d;

	i = 0;
	s = 0;
	d = 0;
	if_in_quote(&d, &s, &i, comm);
	if (g_all.env == 1)
		ft_echo_env(comm, g_all.alst, g_all.err, 0);
	while (comm && comm[i] && g_all.env != 1)
	{
		if (s == 1)
			while (comm[i] != '\'' && comm[i] != '$')
				ft_putchar_fd(comm[i++], 1);
		else if (d == 1)
			while (comm[i] != '\"' && comm[i] != '$') // change for echo "word\""
			{
				if (!comm[i])
					return ;
				ft_putchar_fd(comm[i++], 1);
			}
		i++;
	}
	g_all.quote = 0;
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
		skipspace(comm[i], &j);
		if (comm[i][j] == '$')
			ft_echo_env(comm[i], all->alst, all->err, &j);
		if (comm[i][j] == '-')
			ft_check_n(&i, &res, comm[i], &opt);
		if ((comm[i][j] == '\"' || comm[i][j] == '\'') && !res)
			ft_echo_quote(&comm[i][j]);
		else if (comm[i][j] != '-')
			ft_putstr_fd(&comm[i][j], 1);
		if (comm[i + 1] && ft_strncmp(opt, "-n", 2) && g_all.env != -1)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!ft_strncmp(opt, "off", 3))
		ft_putchar_fd('\n', 1);
	all->err = 0;
}
