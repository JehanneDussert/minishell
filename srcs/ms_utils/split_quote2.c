/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:10:47 by idussert          #+#    #+#             */
/*   Updated: 2021/01/14 16:17:52 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	if_in_quote(int *d, int *s, char *str, t_all *all)
{
	int i;

	i = 0;
	*s = 0;
	*d = 0;
	while (str[i])
	{
		if (str[i] == '$')
			all->env = 1;
		else if (str[i] == '\"')
			while (str[i] && str[i + 1] && str[++i] != '\"')
			{
				//all->quote = 1;
				(*d)++;
			}
		else if (str[i] == '\'')
		{
			while (str[i] && str[i + 1] && str[++i] != '\'')
			{
				//all->quote = 1;
				(*s)++;
			}
		}
		i++;
	}
}

void	ft_env(char *comm, char *new, t_all *all)
{
	char	*tmp;
	int		i;
	int		j;

	i = 1;
	j = 0;
	tmp = comm;
	while (comm[i])
	{
		while (comm[i] == '?' || comm[i] == '{' || comm[i] == '$')
		{
			if (comm[i] == '?' || comm[i] == '$')
				new[j] = comm[i];
			(j)++;
			(i)++;
		}
		while (comm[i] && comm[i] != ' ' && comm[i] != '$' && comm[i] != '\'' &&
			comm[i] != '\"' && comm[i] != '=' && comm[i] != '\\' &&
			comm[i] && comm[i] != '}')
			(i)++;
		tmp = ft_substr(comm, j, ((i - j)));
		ft_putendl_fd("lo", 2);
		ft_check_env(all, &tmp, &new, &j);
		if (comm[i] == '\"')
			return ;
	}
}

void	ft_delete_quotes(char comm, char ***tmp, int *j, char c)
{
	if (comm != c)
	{
		(*tmp)[0][*j] = comm;
		(*j)++;
	}
}

void	ft_copy_comd(char **comm, char **new, int d, int s, t_all *all)
{
	int	i;
	int	j;
	int res;

	i = 0;
	j = 0;
	res = 0;
	if_in_quote(&d, &s, comm[0], all);
	while (comm[0] && comm[0][i])
	{
		if (comm[0][i] == '#')
		{
			new[0][j] = '\0';
			return ;
		}
		else if (comm[0][i] == '\\' && (i == 0 || comm[0][i - 1] != '\\' || res == 1))
		{
			if (res == 1)
				res = 0;
			++i;
			ft_cmd_fill(comm, &new, &i, &j);
			res = 1;
		}
		else if (comm[0][i] == '\"')
		{
			++i;
			if (comm[0][i] == '$')
				ft_env(&comm[0][i], &new[0][j], all);
			while (comm[0][i] && comm[0][i] != '\\' && comm[0][i] != '\"' && d >= 0)
			{
				ft_delete_quotes(comm[0][i], &new, &j, '\"');
				d--;
				i++;
			}
			i++;
		}
		else if (comm[0][i] == '\'')
		{
			++i;
			if (comm[0][i] == '$')
				ft_env(&comm[0][i], &new[0][j], all);
			while (comm[0][i] != '\'' && s >= 0)
			{
				ft_delete_quotes(comm[0][i], &new, &j, '\'');
				s--;
				i++;
			}
			i++;
		}
		while (comm[0][i] && comm[0][i] != '#' && comm[0][i] != '\\'
			&& comm[0][i] != '\'' && comm[0][i] != '\"')
			ft_cmd_fill(comm, &new, &i, &j);
	}
}

char	*ft_clear_quotes(char **comm, t_all *all)
{
	int		w;
	char	*new;

	w = ft_strlen(comm[0]);
	if ((new = ft_calloc(w + 1, sizeof(char))) == NULL)
		return (NULL);
	ft_copy_comd(comm, &new, 0, 0, all);
	free_read(NULL, comm);
	if (new)
	{
		comm[0] = ft_strdup(new);
		ft_free((void **)&new);
	}
	return (comm[0]);
}

void	ft_check_quotes(char ***comm, t_all *all)
{
	int	i;

	i = 0;
	while ((*comm)[i])
	{
		(*comm)[i] = ft_clear_quotes(&((*comm)[i]), all);
		return ;
		i++;
	}
}
