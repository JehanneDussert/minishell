/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:18:45 by ede-banv          #+#    #+#             */
/*   Updated: 2021/01/12 12:13:28 by jdussert         ###   ########.fr       */
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

void	ft_echo_quote(char **comm, int *i)
{
	int	j;
	int	s;
	int	d;

	j = 0;
	while (comm[j])
	{
		s = 0;
		d = 0;
		*i = 0;
		if_in_quote(&d, &s, comm[j]);
		if (g_all.env == 1 && ft_env_in_quote(comm[j]))
			ft_echo_env(comm[j], g_all.alst, g_all.err, i);
		while (comm[j][*i])
		{
			if (comm[j][*i] == '\"')
			{
				while (d > 0 && comm[j][*i])
				{
					ft_putchar_fd(comm[j][++(*i)], 1);
					d--;
				}
			}
			else if (comm[j][*i] == '\'')
			{
				while (s > 0 && comm[j][*i])
				{
					ft_putchar_fd(comm[j][++(*i)], 1);
					s--;
				}
			}
			else if (comm[j][*i])
				ft_putchar_fd(comm[j][*(i)], 1);
			(*i)++;
		}
		if (comm[j + 1] && (comm[j + 1][0] == '\'' || comm[j + 1][0] == '\"'))
			ft_putchar_fd(' ', 1);
		else if (comm[j + 1] && !(comm[j + 1][0] == '\'' || comm[j + 1][0] == '\"'))
			return ;
		j++;
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
		if ((comm[i][j] == '\"' || comm[i][j] == '\'') && !res && g_all.quote)
			ft_echo_quote(&comm[i], &j);
		else if (comm[i][j] != '-')
			while (comm[i][j] && comm[i][j] != '\'' && comm[i][j] != '\"')
				ft_putchar_fd(comm[i][j++], 1);
		if (comm[i + 1] && ft_strncmp(opt, "-n", 2) && g_all.env != -1)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!ft_strncmp(opt, "off", 3))
		ft_putchar_fd('\n', 1);
	all->err = 0;
}
