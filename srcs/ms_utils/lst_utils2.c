/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:33:43 by ede-banv          #+#    #+#             */
/*   Updated: 2021/01/11 10:30:00 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		create_words(char **w1, char **w2, char *cmd)
{
	char *ptr;

	if ((ptr = ft_strchr(cmd, '=')))
	{
		*ptr = '\0';
		if (!(*w1 = ft_strdup(cmd)))
			return (0);
		if (!(*w2 = ft_strdup(ptr + 1)))
		{
			ft_free((void **)&w1);
			return (0);
		}
	}
	else
	{
		if (!(*w1 = ft_strdup(cmd)))
			return (0);
		*w2 = NULL;
	}
	return (1);
}

void	lst_add_env(char **env, t_all *all)
{
	int		i;
	t_lst	*tmp;
	char	*w1;
	char	*w2;

	i = 0;
	while (env && env[i])
	{
		if (!create_words(&w1, &w2, env[i]))
		{
			ft_malloc_error(NULL);
			all->err = 1;
			return ;
		}
		if (!(tmp = ft_lstnew_ms(w1, w2)))
		{
			ft_malloc_error(NULL);
			all->err = 1;
			return ;
		}
		ft_lstadd_back_ms(&all->alst, tmp);
		i++;
	}
}

void	ft_check_env(t_lst *alst, char **tmp)
{
	while (alst)
	{
		if (!ft_strcmp(*tmp, alst->key))
		{
			g_all.env = 0;
			ft_putstr_fd(alst->content, 1);
			ft_free((void **)tmp);
			return ;
		}
		else
			g_all.env = -1;
		alst = alst->next;
	}
	ft_free((void **)tmp);
}
