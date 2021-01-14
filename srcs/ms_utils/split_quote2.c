/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:10:47 by idussert          #+#    #+#             */
/*   Updated: 2021/01/14 12:08:57 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	if_in_quote(int *d, int *s, char *str)
{
	int i;

	i = 0;
	*s = 0;
	*d = 0;
	while (str[i])
	{
		//ft_putstr_fd("ici :", 2);
		//ft_putchar_fd(str[i], 2);
		//ft_putendl_fd("", 2);
		if (str[i] == '$')
			g_all.env = 1;
		else if (str[i] == '\"')
			while (str[++i] && ((str[i] == '\"' && str[i - 1] == '\\') || str[i] != '\"'))
			{
				//ft_putchar_fd(str[i], 2);
				g_all.quote = 1;
				(*d)++;
			}
		else if (str[i] == '\'')
		{
			while (str[i] && str[++i] != '\'')
			{
				g_all.quote = 1;
				(*s)++;
			}
		}
		i++;
	}
}

void	ft_delete_quotes(char comm, char ***tmp, int *j, char c)
{
	if (comm != c)
	{
		//if (c == '\"' && comm[0][*i] == '$')
		//	ft_env();
		(*tmp)[0][*j] = comm;
		(*j)++;
	}
}

void	ft_copy_comd(char **comm, char **new, int d, int s)
{
	int	i;
	int	j;
	int res;

	i = 0;
	j = 0;
	if_in_quote(&d, &s, comm[0]);
	while (comm[0] && comm[0][i])
	{
		res = 0;
		if (comm[0][i] == '#')
		{
			new[0][j] = '\0';
			return ;
		}
		else if (comm[0][i] == '\\' && (i == 0 || comm[0][i - 1] != '\\'))
		{
			++i;
			res = 1;
			ft_cmd_fill(comm, &new, &i, &j);
		}
		else if (comm[0][i] == '\"')
		{
			++i;
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
			while (comm[0][i] != '\'' && s >= 0)
			{
				ft_delete_quotes(comm[0][i], &new, &j, '\'');
				s--;
				i++;
			}
			i++;
		}
		while (comm [0][i] && ((comm[0][i] != '#' && comm[0][i] != '\\') 
			|| res == 1) && comm[0][i] != '\'' && comm[0][i] != '\"')
			ft_cmd_fill(comm, &new, &i, &j);
	}
}

char	*ft_clear_quotes(char **comm)
{
	int		w;
	char	*new;

	w = ft_strlen(comm[0]);
	if ((new = ft_calloc(w + 1, sizeof(char))) == NULL)
		return (NULL);
	ft_copy_comd(comm, &new, 0, 0);
	free_read(NULL, comm);
	if (new)
	{
		comm[0] = ft_strdup(new);
		ft_free((void **)&new);
	}
	return (comm[0]);
}

void	ft_check_quotes(char ***comm)
{
	int	i;

	i = 0;
	while ((*comm)[i])
	{
		ft_nb_backslash((*comm)[i]);
		(*comm)[i] = ft_clear_quotes(&((*comm)[i]));
		return ;
		i++;
	}
}
