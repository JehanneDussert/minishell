/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:10:47 by idussert          #+#    #+#             */
/*   Updated: 2021/01/18 16:38:35 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(char *comm, char ***new, t_copy *copy, t_all *all)
{
	char	*tmp;
	int 	k;
	int 	res;

	++(copy->i);
	k = copy->i;
	tmp = &comm[copy->i];
	if (comm[copy->i])
	{
		if ((comm[copy->i] == '?' && (comm[copy->i - 1] == '$' || comm[copy->i - 1] == '{'))
			|| (comm[copy->i] == '{' && comm[copy->i - 1] == '$') || comm[copy->i] == '$')
			ft_err_nb(comm, new, copy, all);
		while (comm[copy->i] && comm[copy->i] != ' ' && comm[copy->i] != '$' && comm[copy->i] != '\'' &&
			comm[copy->i] != '\"' && comm[copy->i] != '=' && comm[copy->i] != '\\' &&
			comm[copy->i] && comm[copy->i] != '}')
			(copy->i)++;
		tmp = ft_substr(comm, k, (copy->i - k));
		res = ft_check_env(all->alst, tmp, new);
		if (copy->i - k < res)
			all->cmd_len += res;
		if (comm[copy->i] == '\"')
			++(copy->i);
		tmp = ft_strdup((*new)[0]);
		free_read(NULL, (*new));
		k = 0;
		copy->j = 0;
		if (((*new)[0] = ft_calloc(all->cmd_len + 1, sizeof(char))) == NULL)
			return ;
		while (tmp[k])
			ft_cmd_fill(&tmp, new, &k, &copy->j);
		ft_free((void **)&tmp);
	}
}

void	ft_copy_comd(char **comm, char **new, t_all *all)
{
	t_copy	copy;
	
	ft_init_copy(&copy);
	while (comm[0] && comm[0][copy.i])
	{
		if (!ft_check_special_case(comm, &new, &copy, all))
			return ;
		else if (comm[0][copy.i] == '\\' && (copy.i == 0 || comm[0][copy.i - 1] != '\\') && ++(copy.i))
			ft_cmd_fill(comm, &new, &copy.i, &copy.j);
		if (comm[0][copy.i] == '\"')
			ft_double_quote(comm, &copy, &new, all);\
		if (comm[0][copy.i] == '\'')
			ft_simple_quote(comm, &copy, &new);
		while (comm[0][copy.i] && !is_charset(comm[0][copy.i], "#?") && comm[0][copy.i] != '\\'
			&& comm[0][copy.i] != '\'' && comm[0][copy.i] != '\"')
			ft_no_quote(comm, &new, &copy, all);
	}
}

char	*ft_clear_quotes(char **comm, t_all *all)
{
	char	*new;

	all->cmd_len = ft_strlen(comm[0]);
	if ((new = ft_calloc(all->cmd_len + 1, sizeof(char))) == NULL)
		return (NULL);
	ft_copy_comd(comm, &new, all);
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
