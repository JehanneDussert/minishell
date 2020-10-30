/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:18:45 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/26 16:35:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_env(char *comm, t_lst *alst, int err)
{
	char	*tmp;

	tmp = comm;
tmp = ft_strtrim(tmp, "{}");
	if (tmp[0] == '?')
	{
		ft_putnbr_fd(err, 1);
		return ;
	}
	while (alst)
	{
		if (!ft_strcmp(tmp, alst->key))
		{
			ft_putstr_fd(alst->content, 1);
			return ;
		}
		alst = alst->next;
	}
	ft_free((void **)&tmp);
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

void	ft_echo(char **comm, t_all *all)
{
	int		i;
	char	*opt;
	int		res;

	ft_init_echo(&i, &opt, &res);
	while (comm[i])
	{
		if (i == 1 && comm[i][0] == '-')
			ft_check_n(&i, &res, comm[i], &opt);
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
