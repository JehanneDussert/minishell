/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:10:47 by idussert          #+#    #+#             */
/*   Updated: 2021/01/29 10:56:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_copy_comd(char **comm, char **new, t_all *all)
{
	t_copy	copy;

	ft_init_copy(&copy, comm[0]);
	while (comm[0] && comm[0][copy.i])
	{
		if (!ft_check_special_case(comm, &new, &copy, all))
			return ;
		else if (comm[0][copy.i] == '\\' &&
			!ft_check_bs((*comm), copy.i) && ++(copy.i))
		{
			if (!(comm[0][copy.i]))
				return ;
			ft_cmd_fill(comm, &new, &copy.i, &copy.j);
		}
		if (comm[0][copy.i] == '\"')
			ft_double_quote(comm, &copy, &new, all);
		if (comm[0][copy.i] == '\'')
			ft_simple_quote(comm, &copy, &new);
		while ((comm[0][copy.i] && !is_charset(comm[0][copy.i], "#?")
			&& comm[0][copy.i] != '\\'
			&& comm[0][copy.i] != '\'' && comm[0][copy.i] != '\"') ||
			(comm[0][copy.i] == '\\' && ft_check_bs((*comm), copy.i)))
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
	ft_restablish_char(comm);
	while ((*comm)[i])
	{
		(*comm)[i] = ft_clear_quotes(&((*comm)[i]), all);
		return ;
		i++;
	}
}
