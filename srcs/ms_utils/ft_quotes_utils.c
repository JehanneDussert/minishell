/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 21:02:20 by jehannedu         #+#    #+#             */
/*   Updated: 2021/01/27 15:41:18 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_delete_quotes(char comm, char ***tmp, int *j, char c)
{
	if (comm != c)
	{
		if (comm == ' ')
			(*tmp)[0][*j] = 1;
		else
			(*tmp)[0][*j] = comm;
		(*j)++;
	}
}

void	if_in_quote(int *d, int *s, char *str)
{
	int i;

	i = 0;
	*s = 0;
	*d = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			while (str[i] && str[i + 1] && str[++i] != '\"')
				(*d)++;
		else if (str[i] == '\'')
			while (str[i] && str[i + 1] && str[++i] != '\'')
				(*s)++;
		i++;
	}
}

int		ft_check_special_case(char **comm, char ***new, t_copy *copy,
		t_all *all)
{
	if (comm[0][copy->i] == '#')
	{
		(*new)[0][copy->j] = '\0';
		return (0);
	}
	ft_err_nb(comm[0], new, copy, all);
	return (1);
}

void	ft_err_nb(char *comm, char ***new, t_copy *copy, t_all *all)
{
	char *nb;

	while (comm[copy->i] == '?' || comm[copy->i] == '{' || comm[copy->i] == '$'
		|| comm[copy->i] == '}')
	{
		if (comm[copy->i] == '?')
		{
			nb = ft_itoa(all->err);
			all->cmd_len += ft_strlen(nb);
			if (nb)
			{
				(*new)[0] = ft_strjoin_free((*new)[0], nb, 1);
				ft_free((void **)&nb);
			}
		}
		copy->j++;
		copy->i++;
	}
}

void	ft_check_if_err_nb(char *comm, t_copy *copy, char ***new, t_all *all)
{
	if ((comm[copy->i] == '?' && (comm[copy->i - 1] == '$' ||
		comm[copy->i - 1] == '{')) || (comm[copy->i] == '{' &&
		comm[copy->i - 1] == '$') || comm[copy->i] == '$')
		ft_err_nb(comm, new, copy, all);
}
